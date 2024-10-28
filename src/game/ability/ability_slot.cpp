#include <game/ability/ability_slot.h>
#include <game/entity_name.h>

ability_slot::ability_slot(entity &attached_to)
    : component(attached_to)
    , _ability(nullptr)
    , _indicator(nullptr)
    , _indicator_renderer(nullptr)
{
}

ability_slot::~ability_slot()
{
    _messenger.unsubscribe<ability_expired>(*this);
}

void ability_slot::initialize()
{
    entity &indicator_entity = *attached_to().find(entity_name::ability_indicator);
    _indicator = &indicator_entity.attached_component<ability_indicator>();
    _indicator_renderer = &indicator_entity.attached_component<ability_indicator_renderer>();
}

void ability_slot::detach()
{
    remove(*_ability);
}

void ability_slot::receive(const ability_expired &message)
{
    remove(message.ability);
}

void ability_slot::remove(ability &removed)
{
    if (!_ability || &removed != _ability)
    {
        return;
    }
    
    _ability->destroy();
    _ability = nullptr;
    _messenger.unsubscribe<ability_expired>(*this);
}