#include <engine/time_point.h>

time_point::time_point()
    : time_point(0)
{
}

time_point::time_point(float seconds)
    : _seconds(seconds)
{
}

time_point &time_point::operator=(float seconds)
{
    _seconds = seconds;

    return *this;
}