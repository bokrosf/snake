#ifndef SNAKE_GAMEENGINE_COLLISION_COLLISIONENGINE_H
#define SNAKE_GAMEENGINE_COLLISION_COLLISIONENGINE_H

#include <unordered_set>
#include <game_engine/scene.h>
#include <game_engine/entity.h>
#include "box_collider.h"
#include "collision_handler.h"

class collision_engine
{
public:
    collision_engine() = default;
    void detect_collisions(const scene &scene);
private:
    std::vector<box_collider *> collect_colliders(const scene &scene) const;
    void notify_collided_entities(box_collider &collider, const std::unordered_set<entity *> &collided_entities) const;
};

#endif
