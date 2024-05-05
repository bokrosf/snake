#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include <queue>
#include <ranges>
#include <unordered_set>
#include <engine/component/component.h>
#include <engine/entity.h>
#include <engine/object_initializer.h>

class scene
{
public:
    virtual ~scene();
    virtual void initialize() = 0;
    void update_root_status(entity &entity);
    void register_created_entity(entity &created);
    void register_added_component(component &added);
    void initialize_objects();
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
    void destroy_components();
    void destroy_entities();
    
    std::unordered_set<entity *> _root_entities;
    std::unordered_set<entity *> _entities_with_destroyed_component;
    std::unordered_set<entity *> _entities_to_destroy;
    object_initializer _initializer;
};

#endif
