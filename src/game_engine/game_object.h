#ifndef SNAKE_GAMEENGINE_GAMEOBJECT_H
#define SNAKE_GAMEENGINE_GAMEOBJECT_H

#include <vector>
#include <algorithm>
#include <ranges>
#include <stdexcept>
#include <concepts>
#include <utility>
#include "activatable.h"
#include "component/component.h"
#include "component/component_not_found.h"
#include "life_state.h"
#include "messaging/messenger.h"
#include "component_added.h"
#include <game_engine/scene.h>

class game_object : public activatable 
{
public:
    game_object(const game_object &other) = delete;
    game_object(game_object &&other) = delete;
    ~game_object();
    static game_object &create();
    void destroy();
    life_state life_state() const;
    game_object *parent() const;
    void attach_to(game_object *new_parent);
    
    auto children() const
    {
        return std::views::all(_children);
    }

    template<typename T, typename... Args>
        requires std::derived_from<T, component>
    T &add_component(Args&&... args);

    template<typename T>
        requires std::derived_from<T, component>
    T *find_component() const;

    template<typename T>
        requires std::derived_from<T, component>
    T &attached_component() const;

    template<typename T>
        requires std::derived_from<T, component>
    auto all_attached_components() const
    {
        auto conversion = [](component *c) { return dynamic_cast<T *>(c); };
        
        return _components | std::views::filter(conversion) | std::views::transform(conversion);
    }

    template<typename T>
        requires std::derived_from<T, component>
    void destroy_component();
private:
    game_object();
    ::life_state _life_state;
    messenger &_messenger;
    game_object *_parent;
    std::vector<game_object *> _children;
    std::vector<component *> _components;
    game_object *find_descendant_tree_root(game_object *descendant) const;
    void change_parent(game_object *object, game_object *new_parent);
    void erase_destroyed_components();
    friend void scene::destroy_components();
};

template<typename T, typename... Args>
    requires std::derived_from<T, component>
T &game_object::add_component(Args&&... args)
{
    T *component = nullptr;
    
    try
    {
        component = new T(*this, std::forward<Args>(args)...);
    }
    catch (...)
    {
        delete component;
        throw;
    }

    _components.push_back(component);
    _messenger.send(component_added(*component));

    return *component;
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

    return component ? *component : throw component_not_found(std::string("Not found component of type: ").append(typeid(T).name()));
}

template<typename T>
    requires std::derived_from<T, component>
void game_object::destroy_component()
{
    if (component *component = find_component<T>())
    {
        component->destroy();
    }
}

#endif
