#include <stdexcept>
#include <game/food/food_spawner.h>

food_spawner::food_spawner(entity &attached_to, int food_count)
    : component(attached_to)
    , _remaining_food_count(food_count)
{
    if (food_count < 1)
    {
        throw std::invalid_argument("Food count must be greater than zero.");
    }
}

void food_spawner::spawn()
{
    if (_remaining_food_count <= 0)
    {
        _messenger.send(game_event::food_storage_depleted);
    }
    
    // TODO 2024-05-03 Generate food between the bounds of the tile_maze.
}
