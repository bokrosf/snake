#ifndef SNAKE_GAMEENGINE_SCENE_H
#define SNAKE_GAMEENGINE_SCENE_H

#include <unordered_set>
#include <queue>
#include "game_object.h"
#include "component/component.h"

class scene
{
public:
    scene();
private:
    std::unordered_multiset<game_object *> _root_objects;
    std::queue<component *> _components_to_initialize;
};

#endif
