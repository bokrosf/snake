#ifndef ENGINE_GAMETIME_H
#define ENGINE_GAMETIME_H

namespace game_time
{
    using context_id = int;

    void initialize(context_id id);
    void reset_delta_time(context_id id);
    void end_frame();
    float delta();
    float now();
    float real_now();
}

#endif
