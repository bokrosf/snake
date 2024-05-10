#ifndef ENGINE_SCENETRAVERSAL_H
#define ENGINE_SCENETRAVERSAL_H

#include <functional>
#include <engine/scene.h>

namespace scene_traversal
{
    void traverse(const scene &scene, std::function<bool(const entity *)> filter, std::function<void(entity *)> operation);
}

#endif