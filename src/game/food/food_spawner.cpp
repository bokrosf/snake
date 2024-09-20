#include <stdexcept>
#include <engine/collision/box_collider.h>
#include <game/entity_names.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>
#include <game/food/food_spawner.h>
#include <game/tag.h>

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
    _tile_maze = &attached_to().find(entity_names::map)->attached_component<tile_maze>();
    _snake = &attached_to().find_tagged(tag::snake)->attached_component<snake>();
}

void food_spawner::start()
{
    for (entity *wall : attached_to().find_all_tagged(tag::wall))
    {
        box_collider &collider = wall->attached_component<box_collider>();

        for (const auto &tile_center : _tile_maze->tiles_of_area(wall->transformation().position(), 2.0F * collider.area()))
        {
            _wall_tiles.insert(tile_center);
        }
    }
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
    vector2 food_position = _tile_maze->tile_center(_tile_maze->transformation().position() + vector2(0, y_sign * _tile_maze->tile_size()));
    entity &food = entity::create();
    food.transformation().position(food_position);
    food.add_component<::food>(_tile_maze->tile_size());
    food.add_component<food_renderer>(food_layer, _tile_maze->tile_size());
    food.add_component<box_collider>(0.5F * vector2(_tile_maze->tile_size(), _tile_maze->tile_size()));
    food.attached_component<food_renderer>().change_material(material{SDL_Color{255, 0, 0, 255}});
    --_remaining_food_count;
    y_sign *= -1;
}

std::generator<vector2> food_spawner::snake_tiles() const
{
    auto end = _snake->segments().begin();
    auto start = end++;

    while (end != _snake->segments().end())
    {
        vector2 segment = start->points_to(*end);
        vector2 area = segment + 0.5F * _tile_maze->tile_size() * segment.normalize().perpendicular();
        vector2 center = *start + 0.5F * segment;

        for (const auto &tile_center : _tile_maze->tiles_of_area(center, area))
        {
            co_yield tile_center;
        }

        start = end++;
    }
}
