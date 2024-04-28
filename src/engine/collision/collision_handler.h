#ifndef SNAKE_ENGINE_COLLISION_COLLISIONHANDLER_H
#define SNAKE_ENGINE_COLLISION_COLLISIONHANDLER_H

#include <engine/collision/collision.h>

class collision_handler
{
public:
    virtual void collide(const collision &collision) = 0;
};

#endif
