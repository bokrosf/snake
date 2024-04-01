#ifndef SNAKE_GAMEENGINE_GAMEPLAY_GAMEOBJECT_H
#define SNAKE_GAMEENGINE_GAMEPLAY_GAMEOBJECT_H

#include <vector>
#include <algorithm>
#include <ranges>
#include <typeinfo>
#include <stdexcept>
#include "component.h"
#include "activatable.h"
#include "component_not_found.h"

class component;

class game_object : public activatable 
{
public:
    game_object();
    ~game_object();
    game_object *parent() const;
    void attach_to(game_object *new_parent);
    auto children() const;

    template<typename T>
    void add_component();

    template<typename T>
    T *find_component() const;

    template<typename T>
    T &attached_component() const;

    void erase_component(const component &erased);

    template<typename T>
    void erase_component();
private:
    game_object *_parent;
    std::vector<game_object *> _children;
    std::vector<component *> _components;
};

template<typename T>
void game_object::add_component()
{
    _components.push_back(new T(*this));
}

template<typename T>
T *game_object::find_component() const
{
    auto predicate = [](component *c) { return dynamic_cast<T *>(c); };
    auto it = std::find_if(_components.begin() , _components.end(), predicate);

    return it != _components.end() ? dynamic_cast<T *>(*it) : nullptr;
}

template<typename T>
T &game_object::attached_component() const
{
    T *component = find_component<T>();

    return component ? *component : throw component_not_found("Not found component of type.");
}

template<typename T>
void game_object::erase_component()
{
    if (T *component = find_component<T>())
    {
        erase_component(component);
    }
}

#endif
