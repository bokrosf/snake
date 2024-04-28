#ifndef SNAKE_GAMEENGINE_SCENETRAVERSAL_H
#define SNAKE_GAMEENGINE_SCENETRAVERSAL_H

#include <functional>
#include <game_engine/scene.h>

namespace scene_traversal
{
    bool filter_active_entity(const entity *entity);
    void traverse(const scene &scene, std::function<bool(const entity *)> filter, std::function<void(entity *)> operation);
}

#endif