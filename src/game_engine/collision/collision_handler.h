#ifndef SNAKE_GAMEENGINE_COLLISION_COLLISIONHANDLER_H
#define SNAKE_GAMEENGINE_COLLISION_COLLISIONHANDLER_H

#include "collision.h"

class collision_handler
{
public:
    virtual void collide(const collision &collision) = 0;
};

#endif
