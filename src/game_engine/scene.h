#ifndef SNAKE_GAMEENGINE_SCENE_H
#define SNAKE_GAMEENGINE_SCENE_H

#include <unordered_set>
#include <queue>
#include <ranges>
#include "game_object.h"
#include "component/component.h"
#include "game_object_parent_changed.h"
#include "component_added.h"

class scene
{
public:
    virtual ~scene() = default;
    virtual void initialize() = 0;
    void update_root_objects(const game_object_parent_changed &message);
    void register_added_component(const component_added &message);
    void initialize_components();
    std::ranges::ref_view<const std::unordered_set<game_object *>> root_objects() const;
protected:
    scene() = default;
private:
    std::unordered_set<game_object *> _root_objects;
    std::queue<component *> _components_to_initialize;
};

#endif
