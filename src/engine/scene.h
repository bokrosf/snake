#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include <map>
#include <queue>
#include <ranges>
#include <string>
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
    void add(entity &entity);
    void add(component &component);
    void initialize_objects();
    void mark_as_destroyed(component &component);
    void mark_as_destroyed(entity &entity);
    void destroy_marked_objects();
    void reset();
    entity *find_entity(const std::string &name) const;

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
    std::map<std::string, entity *> _named_entities;
};

#endif
