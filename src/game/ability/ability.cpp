#include <stdexcept>
#include <engine/game_time.h>
#include <game/ability/ability.h>
#include <game/ability/ability_expired.h>
#include <game/ability/ability_usage_changed.h>
#include <game/tag.h>

ability::ability(entity &attached_to, float duration)
    : behavior(attached_to)
    , _duration(duration)
{
    if (_duration <= 0)
    {
        std::runtime_error("Duration must be greater than zero.");
    }
}

void ability::initialize()
{
    _snake = &attached_to().find_tagged(tag::snake)->attached_component<::snake>();
}

void ability::start()
{
    _expiration = game_time::now() + _duration;
    _messenger.send(ability_usage_changed{*this, 100});
}

void ability::update()
{
    if (life_state() != life_state::alive)
    {
        return;
    }

    if (game_time::now() > _expiration)
    {
        _messenger.send(ability_expired{*this});
        destroy();
        
        return;
    }

    update_effect();
    float remaining_percentage = (_expiration - game_time::now()) / _duration;
    _messenger.send(ability_usage_changed{*this, remaining_percentage});
}

::snake &ability::snake() const
{
    return *_snake;
}

void ability::update_effect()
{
}
