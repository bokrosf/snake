#ifndef SNAKE_GAME_FOOD_FOODSPAWNER_H
#define SNAKE_GAME_FOOD_FOODSPAWNER_H

#include <engine/component/component.h>
#include <engine/entity.h>
#include <game/game_event.h>

class food_spawner : public component
{
public:
    food_spawner(entity &attached_to, int food_count);
    ~food_spawner() override = default;
    void spawn();
private:
    int _remaining_food_count;
};

#endif
