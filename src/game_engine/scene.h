#ifndef SNAKE_GAMEENGINE_SCENE_H
#define SNAKE_GAMEENGINE_SCENE_H

#include <unordered_set>
#include <queue>
#include <ranges>
#include "game_object.h"
#include "component/component.h"

class scene
{
public:
    virtual ~scene();
    virtual void initialize() = 0;
    void update_root_status(game_object &object);
    void register_added_component(component &added);
    void initialize_components();    
    void mark_as_destroyed(game_object &object);
    void destroy_marked_objects();

    auto root_objects() const
    {
        return std::views::all(_root_objects);
    }
protected:
    scene() = default;
private:
    std::unordered_set<game_object *> _root_objects;
    std::queue<component *> _components_to_initialize;
    std::unordered_set<game_object *> _objects_to_destroy;
};

#endif
