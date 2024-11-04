#include <engine/entity.h>
#include <game/ability/ability_indicator.h>

ability_indicator::ability_indicator()
    : _percentage(0)
    , _ability(nullptr)
{
}

ability_indicator::~ability_indicator()
{
    _messenger.unsubscribe<ability_usage_changed>(*this);
    _messenger.unsubscribe<ability_expired>(*this);
}

void ability_indicator::track(::ability &ability)
{
    stop_tracking();
    _messenger.subscribe<ability_usage_changed>(*this);
    _messenger.subscribe<ability_expired>(*this);
    _ability = &ability;
    _percentage = 0.0F;
    attached_to().active(true);
}

float ability_indicator::percentage() const
{
    return _percentage;
}

void ability_indicator::receive(const ability_usage_changed &message)
{
    if (&message.ability == _ability)
    {
        _percentage = message.remaining_percentage;
    }
}

void ability_indicator::receive(const ability_expired &message)
{
    if (&message.ability == _ability)
    {
        stop_tracking();
    }
}

void ability_indicator::stop_tracking()
{
    if (!_ability)
    {
        return;
    }
    
    _ability = nullptr;
    attached_to().active(false);
    _messenger.unsubscribe<ability_usage_changed>(*this);
    _messenger.unsubscribe<ability_expired>(*this);
}
