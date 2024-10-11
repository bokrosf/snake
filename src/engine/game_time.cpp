#include <SDL2/SDL.h>
#include <engine/game_time.h>

namespace
{
    const float precision = 0.001F;
    Uint64 frame_started_at = 0;
    Uint64 frame_ended_at = 0;
    float delta = 0;
}

void game_time::reset_delta_time()
{
    frame_started_at = SDL_GetTicks64();
    frame_ended_at = frame_started_at;
    delta = 0;
}

void game_time::end_frame()
{
    frame_ended_at = SDL_GetTicks64();
    delta = precision * (frame_ended_at - frame_started_at);
    frame_started_at = frame_ended_at;
}


float game_time::delta_time()
{
    return delta;
}

float game_time::now()
{
    return precision * frame_started_at;
}

float game_time::real_now()
{
    return precision * SDL_GetTicks64();
}