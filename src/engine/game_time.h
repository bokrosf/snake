#ifndef ENGINE_GAMETIME_H
#define ENGINE_GAMETIME_H

class time_point;

namespace game_time
{
    using context_id = int;

    void initialize(context_id id);
    void reset(context_id id);
    void end_frame();
    float delta();
    float now();
    float real_now();
    time_point &bind(float seconds = 0);
    void unbind(time_point &bounded);
}

#endif
