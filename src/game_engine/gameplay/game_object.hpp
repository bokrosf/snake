#ifndef SNAKE_GAMEENGINE_GAMEPLAY_GAMEOBJECT_H
#define SNAKE_GAMEENGINE_GAMEPLAY_GAMEOBJECT_H

#include <vector>
#include <algorithm>
#include <ranges>
#include <typeinfo>
#include <stdexcept>
#include "component.h"
#include "updatable.h"
#include "activatable.h"
#include "component_not_found.h"

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
    T* find_component() const;

    template<typename T>
    T &attached_component() const;

    void erase_component(const component &c);

    template<typename T>
    void erase_component();
private:
    game_object *_parent;
    std::vector<game_object *> _children;
    std::vector<component *> _components;
};

game_object::game_object()
    : _parent(nullptr)
{
}

game_object::~game_object()
{
    for (auto c : _components)
    {
        delete c;
    }
}

game_object *game_object::parent() const
{
    return _parent;
}

void game_object::attach_to(game_object *new_parent)
{
    if (new_parent == this)
    {
        throw std::invalid_argument("Current instance can not be it's own parent.");
    }

    if (new_parent == _parent)
    {
        return;
    }

    if (_parent)
    {
        _children.erase(std::find(_children.begin(), _children.end(), this));
    }

    _parent = new_parent;
    
    if (_parent)
    {
        _parent->_children.push_back(this);
    }
}

auto game_object::children() const
{
    auto reference_transformer = [](const game_object *go) { return *go; };

    return std::views::all(_children) | std::views::transform(reference_transformer);
}

template<typename T>
void game_object::add_component()
{
    _components.push_back(new T(*this));
}

template<typename T>
T* game_object::find_component() const
{
    auto predicate = [](component *c) { return dynamic_cast<T *>(c); };
    auto it = std::find_if(_components.begin() , _components.end(), predicate);

    return it != _components.end() ? &(*it) : nullptr;
}

template<typename T>
T &game_object::attached_component() const
{
    T* component = find_component<T>();

    return component ? *component : throw component_not_found("Not found component of type.");
}

void game_object::erase_component(const component &erased)
{
    auto it = std::find(_components.begin(), _components.end(), &erased);

    if (it != _components.end())
    {
        delete *it;
        _components.erase(it);
    }
}

template<typename T>
void game_object::erase_component()
{
    if (T* component = find_component<T>())
    {
        erase_component(component);
    }
}

#endif
