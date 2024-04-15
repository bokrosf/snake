#ifndef SNAKE_GAMEENGINE_GAMEOBJECTDESTROYREQUESTED_H
#define SNAKE_GAMEENGINE_GAMEOBJECTDESTROYREQUESTED_H

#include "game_object.h"

struct game_object_destroy_requested
{
    game_object &object;

    game_object_destroy_requested(game_object &object)
        : object(object)
    {
    }
};

#endif
