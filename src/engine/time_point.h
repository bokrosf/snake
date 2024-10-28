#ifndef ENGINE_TIMEPOINT_H
#define ENGINE_TIMEPOINT_H

#include <engine/game_time.h>

class time_point
{
public:
    time_point();
    explicit time_point(float seconds);
    time_point &operator=(float seconds);
private:
    float _seconds;

    friend void game_time::reset_delta_time(game_time::context_id);
};

#endif