#include <engine/game_time.h>
#include <engine/time_point.h>

time_point::time_point()
    : time_point(0)
{
}

time_point::~time_point()
{
    unbind();
}

time_point::time_point(float seconds)
    : _seconds(seconds)
    , _bounded(false)
{
}

time_point &time_point::operator=(float seconds)
{
    _seconds = seconds;

    return *this;
}

void time_point::bind()
{
    if (!_bounded)
    {
        game_time::bind(*this);
        _bounded = true;
    }
}

void time_point::unbind()
{
    if (_bounded)
    {
        game_time::unbind(*this);
        _bounded = false;
    }
}