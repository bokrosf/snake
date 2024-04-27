#ifndef SNAKE_GAMEENGINE_SCENETRAVERSAL_H
#define SNAKE_GAMEENGINE_SCENETRAVERSAL_H

#include <functional>
#include "scene.h"

namespace scene_traversal
{
    bool filter_active_object(const game_object *object);
    void traverse(const scene &scene, std::function<bool(const game_object *)> filter, std::function<void(game_object *)> operation);
}

#endif