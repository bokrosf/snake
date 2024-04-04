#ifndef SNAKE_GAMEENGINE_GAMEOBJECTPARENTCHANGED_H
#define SNAKE_GAMEENGINE_GAMEOBJECTPARENTCHANGED_H

#include "game_object.h"

struct game_object_parent_changed
{
    game_object &object;

    game_object_parent_changed(game_object &object)
        : object(object)
    {
    }
};

#endif
