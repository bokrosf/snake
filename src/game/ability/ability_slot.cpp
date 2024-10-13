#include <game/ability/ability_slot.h>

ability_slot::ability_slot(entity &attached_to)
    : component(attached_to)
{
}

void ability_slot::detach()
{
    remove();
}

void ability_slot::remove()
{
    if (!_ability)
    {
        return;
    }
    
    _ability->destroy();
    _ability = nullptr;
}
