#include <stdexcept>
#include <engine/time/game_time.h>
#include <game/ability/ability.h>
#include <game/ability/ability_expired.h>
#include <game/ability/ability_usage_changed.h>
#include <game/entity_name.h>

ability::ability(entity &attached_to, float duration)
    : behavior(attached_to)
    , _duration(duration)
{
    if (_duration <= 0)
    {
        std::runtime_error("Duration must be greater than zero.");
    }
}

void ability::start()
{
    _expiration.bind();
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
        return;
    }

    update_effect();
    float remaining_percentage = (_expiration - game_time::now()) / _duration;
    _messenger.send(ability_usage_changed{*this, remaining_percentage});
}

void ability::update_effect()
{
}