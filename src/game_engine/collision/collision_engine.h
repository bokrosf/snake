#ifndef SNAKE_GAMEENGINE_COLLISION_COLLISIONENGINE_H
#define SNAKE_GAMEENGINE_COLLISION_COLLISIONENGINE_H

#include <game_engine/scene.h>
#include "box_collider.h"
#include "collision_handler.h"

class collision_engine
{
public:
    collision_engine() = default;
    void detect_collisions(const scene *scene);
private:
    std::vector<box_collider *> collect_colliders(const scene *scene);
};

#endif
