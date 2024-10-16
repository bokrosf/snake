#include <game/ability/speed_boost.h>

speed_boost::speed_boost(entity &attached_to, float duration)
    : ability(attached_to, duration)
    , _snake(nullptr)
    , _original_speed(0)
{
}

void speed_boost::initialize()
{
    _snake = &attached_to().attached_component<snake>();
}

void speed_boost::start()
{
    ability::start();
    _original_speed = _snake->speed();
    _snake->speed(2 * _original_speed);
}

void speed_boost::detach()
{
    _snake->speed(_original_speed);
}