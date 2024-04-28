#include "special_ability_slot.h"

special_ability_slot::special_ability_slot(entity &attached_to)
    : component(attached_to)
{
}

void special_ability_slot::detach()
{
    remove();
}

void special_ability_slot::remove()
{
    if (!_ability)
    {
        return;
    }
    
    _ability->destroy();
    _ability = nullptr;
}
