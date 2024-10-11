#ifndef ENGINE_GAMETIME_H
#define ENGINE_GAMETIME_H

namespace game_time
{
    void reset_delta_time();
    void end_frame();
    float delta_time();
    float now();
    float real_now();
}

#endif
