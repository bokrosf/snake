#ifndef SNAKE_GAMEENGINE_GAMETIME_H
#define SNAKE_GAMEENGINE_GAMETIME_H

#include <SDL2/SDL.h>

namespace game_time
{
    float delta_time();
    void update_delta_time(Uint64 frame_started_at, Uint64 frame_ended_at);
}

#endif
