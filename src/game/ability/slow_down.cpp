#include <engine/entity.h>
#include <game/ability/slow_down.h>

slow_down::slow_down(float duration)
    : ability(duration)
    , _snake(nullptr)
    , _original_speed(0)
{
}

void slow_down::initialize()
{
    _snake = &attached_to().attached_component<snake>();
}

void slow_down::start()
{
    ability::start();
    _original_speed = _snake->speed();
    _snake->speed(0.5 * _original_speed);
}

void slow_down::detach()
{
    _snake->speed(_original_speed);
}