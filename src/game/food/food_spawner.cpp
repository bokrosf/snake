#include <stdexcept>
#include <engine/vector2.h>
#include <engine/collision/box_collider.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>
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

void food_spawner::initialize()
{
    _tile_maze = &attached_to().attached_component<tile_maze>();
}

void food_spawner::start()
{
    spawn();
}

void food_spawner::spawn()
{
    if (_remaining_food_count <= 0)
    {
        _messenger.send(game_event::food_storage_depleted);
        return;
    }
    
    // TODO 2024-05-03 Generate food between the bounds of the tile_maze.
    // A temporary solution for testing the component and game ending.
    static int y_sign = 1;
    const int food_layer = 1;
    vector2 food_position = _tile_maze->tile_center(_tile_maze->center() + vector2(0, y_sign * _tile_maze->tile_size()));
    entity &food = entity::create();
    food.add_component<::food>(food_position, _tile_maze->tile_size());
    food.add_component<food_renderer>(food_layer, _tile_maze->tile_size());
    food.add_component<box_collider>(food_position, 0.5F * vector2(_tile_maze->tile_size(), _tile_maze->tile_size()));
    food.attached_component<food_renderer>().change_material(material{SDL_Color{255, 0, 0, 255}});
    --_remaining_food_count;
    y_sign *= -1;
}
