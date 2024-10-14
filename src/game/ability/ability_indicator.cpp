#include <game/ability/ability_indicator.h>

ability_indicator::ability_indicator(entity &attached_to)
    : behavior(attached_to)
    , _percentage(0)
    , _ability(nullptr)
{
}

ability_indicator::~ability_indicator()
{
    stop_tracking();
}

void ability_indicator::track(::ability &ability)
{
    stop_tracking();
    _ability = &ability;
    _percentage = 0.0F;
    attached_to().activate(true);
    _messenger.subscribe<ability_usage_changed>(*this);
    _messenger.subscribe<ability_expired>(*this);
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

    _messenger.unsubscribe<ability_usage_changed>(*this);
    _messenger.unsubscribe<ability_expired>(*this);
    _ability = nullptr;
    attached_to().activate(false);
}
