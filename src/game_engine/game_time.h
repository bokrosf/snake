#ifndef SNAKE_GAMEENGINE_GAMETIME_H
#define SNAKE_GAMEENGINE_GAMETIME_H

#include <SDL2/SDL.h>

namespace game_time
{
    float delta_time();
    void end_frame();
}

#endif
