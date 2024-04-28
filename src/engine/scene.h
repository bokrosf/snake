#ifndef SNAKE_ENGINE_SCENE_H
#define SNAKE_ENGINE_SCENE_H

#include <queue>
#include <ranges>
#include <unordered_set>
#include <engine/component/component.h>
#include <engine/entity.h>

class scene
{
public:
    virtual ~scene();
    virtual void initialize() = 0;
    void update_root_status(entity &entity);
    void register_added_component(component &added);
    void initialize_components();    
    void mark_as_destroyed(component &component);
    void mark_as_destroyed(entity &entity);
    void destroy_marked_objects();

    auto root_entities() const
    {
        return std::views::all(_root_entities);
    }
protected:
    scene() = default;
private:
    std::unordered_set<entity *> _root_entities;
    std::queue<component *> _components_to_initialize;
    std::unordered_set<entity *> _entities_with_destroyed_component;
    std::unordered_set<entity *> _entities_to_destroy;
    void destroy_components();
    void destroy_entities();
};

#endif
