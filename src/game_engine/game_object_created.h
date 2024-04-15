#ifndef SNAKE_GAMEENGINE_GAMEOBJECTCREATED_H
#define SNAKE_GAMEENGINE_GAMEOBJECTCREATED_H

#include "game_object.h"

struct game_object_created
{
    game_object &created;
    
    game_object_created(game_object &created)
        : created(created)
    {
    }
};

#endif
