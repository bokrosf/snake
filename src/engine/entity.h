#ifndef SNAKE_ENGINE_ENTITY_H
#define SNAKE_ENGINE_ENTITY_H

#include <algorithm>
#include <concepts>
#include <ranges>
#include <stdexcept>
#include <vector>
#include <utility>
#include <engine/activatable.h>
#include <engine/component_added.h>
#include <engine/component/component.h>
#include <engine/component/component_not_found.h>
#include <engine/life_state.h>
#include <engine/messaging/messenger.h>

class scene;

class entity : public activatable 
{
public:
    entity(const entity &other) = delete;
    entity(entity &&other) = delete;
    ~entity();
    static entity &create();
    void destroy();
    life_state life_state() const;
    entity *parent() const;
    void attach_to(entity *new_parent);
    
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
    entity();
    ::life_state _life_state;
    messenger &_messenger;
    entity *_parent;
    std::vector<entity *> _children;
    std::vector<component *> _components;
    entity *find_descendant_tree_root(entity *descendant) const;
    void change_parent(entity *entity, ::entity *new_parent);
    void erase_destroyed_components();
    friend scene;
};

template<typename T, typename... Args>
    requires std::derived_from<T, component>
T &entity::add_component(Args&&... args)
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
    _messenger.send(component_added{*component});

    return *component;
}

template<typename T>
    requires std::derived_from<T, component>
T *entity::find_component() const
{
    auto predicate = [](component *c) { return dynamic_cast<T *>(c); };
    auto it = std::find_if(_components.begin() , _components.end(), predicate);
    
    return it != _components.end() ? dynamic_cast<T *>(*it) : nullptr;
}

template<typename T>
    requires std::derived_from<T, component>
T &entity::attached_component() const
{
    T *component = find_component<T>();

    return component ? *component : throw component_not_found(std::string("Not found component of type: ").append(typeid(T).name()));
}

template<typename T>
    requires std::derived_from<T, component>
void entity::destroy_component()
{
    if (component *component = find_component<T>())
    {
        component->destroy();
    }
}

#endif
