#ifndef ENGINE_TIMEPOINT_H
#define ENGINE_TIMEPOINT_H

#include <engine/game_time.h>

class time_point
{
public:
    time_point();
    explicit time_point(float seconds);
    ~time_point();
    time_point &operator=(float seconds);
    operator float() const;
    time_point &operator+=(float duration);
    void bind();
    void unbind();
private:
    float _seconds;
    bool _bounded;

    friend void game_time::reset(game_time::context_id);
};

#endif