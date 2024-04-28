#include "snake_special_ability.h"

snake_special_ability::snake_special_ability(entity &attached_to)
    : component(attached_to)
{
}

snake_special_ability::~snake_special_ability()
{
}

snake *snake_special_ability::snake() const
{
    return attached_to().find_component<::snake>();
}
