#include <game/ability/speed_boost.h>

speed_boost::speed_boost(entity &attached_to, float duration)
    : ability(attached_to, duration)
    , _original_speed(0)
{
}

void speed_boost::start()
{
    ability::start();
    _original_speed = snake().speed();
    snake().speed(2 * _original_speed);
}

void speed_boost::detach()
{
    snake().speed(_original_speed);
}