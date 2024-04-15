#include "game_time.h"

namespace
{
    float delta = 0;
}

float game_time::delta_time()
{
    return delta;
}

void game_time::update_delta_time(Uint64 frame_started_at, Uint64 frame_ended_at)
{
    delta = 0.001F * (frame_ended_at - frame_started_at);
}
