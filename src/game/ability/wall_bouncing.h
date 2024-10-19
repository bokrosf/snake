#ifndef SNAKE_GAME_ABILITY_WALLBOUNCING_H
#define SNAKE_GAME_ABILITY_WALLBOUNCING_H

#include <vector>
#include <game/ability/ability.h>
#include <game/fatal_collision_handler.h>
#include <game/bouncing_collision_handler.h>

class wall_bouncing : public ability
{
public:
    wall_bouncing(entity &attached_to, float duration);
    void start() override;
    void detach() override;
private:
    std::vector<fatal_collision_handler *> _deactivated_handlers;
    std::vector<bouncing_collision_handler *> _added_handlers;
};

#endif