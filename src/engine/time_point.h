#ifndef ENGINE_TIMEPOINT_H
#define ENGINE_TIMEPOINT_H

class time_point
{
public:
    time_point();
    explicit time_point(float seconds);
    time_point &operator=(float seconds);
private:
    float _seconds;
};

#endif