#ifndef SNAKE_GAMEENGINE_GAMEOBJECT_H
#define SNAKE_GAMEENGINE_GAMEOBJECT_H

#include <vector>
#include <algorithm>
#include <ranges>
#include <typeinfo>
#include <stdexcept>
#include <concepts>
#include <utility>
#include "activatable.h"
#include "component/component.h"
#include "component/component_not_found.h"
#include "messaging/messenger.h"
#include "component_added.h"

class component;

class game_object : public activatable 
{
public:
    game_object(messenger &messenger);
    ~game_object();
    game_object *parent() const;
    void attach_to(game_object *new_parent);
    auto children() const;

    template<typename T, typename... Args>
        requires std::derived_from<T, component>
    void add_component(Args&&... args);

    template<typename T>
        requires std::derived_from<T, component>
    T *find_component() const;

    template<typename T>
        requires std::derived_from<T, component>
    T &attached_component() const;

    void erase_component(const component &erased);

    template<typename T>
        requires std::derived_from<T, component>
    void erase_component();
private:
    messenger &_messenger;
    game_object *_parent;
    std::vector<game_object *> _children;
    std::vector<component *> _components;
};

template<typename T, typename... Args>
    requires std::derived_from<T, component>
void game_object::add_component(Args&&... args)
{
    T *component = new T(*this, std::forward<Args>(args)...);
    _components.push_back(component);
    _messenger.send(component_added(*component));
}

template<typename T>
    requires std::derived_from<T, component>
T *game_object::find_component() const
{
    auto predicate = [](component *c) { return dynamic_cast<T *>(c); };
    auto it = std::find_if(_components.begin() , _components.end(), predicate);
    return it != _components.end() ? dynamic_cast<T *>(*it) : nullptr;
}

template<typename T>
    requires std::derived_from<T, component>
T &game_object::attached_component() const
{
    T *component = find_component<T>();

    return component ? *component : throw component_not_found("Not found component of type.");
}

template<typename T>
    requires std::derived_from<T, component>
void game_object::erase_component()
{
    if (T *component = find_component<T>())
    {
        erase_component(component);
    }
}

#endif
