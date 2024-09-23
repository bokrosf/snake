#ifndef SNAKE_GAME_FOOD_FOODSPAWNER_H
#define SNAKE_GAME_FOOD_FOODSPAWNER_H

#include <random>
#include <unordered_set>
#include <engine/component/component.h>
#include <engine/entity.h>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/vector2.h>
#include <game/game_event.h>
#include <game/snake/snake.h>
#include <game/tile_maze/tile_maze.h>

class food_spawner : public component, public initializable, public startable
{
public:
    food_spawner(entity &attached_to);
    ~food_spawner() override = default;
    void initialize() override;
    void start() override;
    void spawn();
private:
    std::unordered_set<vector2> snake_tiles() const;

    std::unordered_set<vector2> _wall_tiles;
    std::random_device _random_generator;
    std::uniform_int_distribution<unsigned int> _tile_distribution;
    unsigned int _remaining_food_count;
    const tile_maze *_tile_maze;
    const snake *_snake;
};

#endif
