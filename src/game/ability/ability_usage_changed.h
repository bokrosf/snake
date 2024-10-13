#ifndef SNAKE_GAME_ABILITY_ABILITYUSAGECHANGED_H
#define SNAKE_GAME_ABILITY_ABILITYUSAGECHANGED_H

#include <game/ability/ability.h>

struct ability_usage_changed
{
    ::ability &ability;
    float remaining_percentage;
};

#endif