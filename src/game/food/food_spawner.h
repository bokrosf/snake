#ifndef SNAKE_GAME_FOOD_FOODSPAWNER_H
#define SNAKE_GAME_FOOD_FOODSPAWNER_H

#include <engine/component/component.h>
#include <engine/entity.h>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <game/game_event.h>
#include <game/tile_maze/tile_maze.h>

class food_spawner : public component, public initializable, public startable
{
public:
    food_spawner(entity &attached_to, int food_count);
    ~food_spawner() override = default;
    void initialize() override;
    void start() override;
    void spawn();
private:
    int _remaining_food_count;
    const tile_maze *_tile_maze;
};

#endif
