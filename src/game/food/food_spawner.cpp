#include <stdexcept>
#include <engine/collision/box_collider.h>
#include <game/color.h>
#include <game/entity_name.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>
#include <game/food/food_spawner.h>
#include <game/game_start_requirement.h>
#include <game/render_layer.h>
#include <game/tag.h>

food_spawner::food_spawner(entity &attached_to)
    : component(attached_to)
    , _remaining_food_count(0)
{
}

void food_spawner::initialize()
{
    _tile_maze = &attached_to().find(entity_name::map)->attached_component<tile_maze>();
    _snake = &attached_to().find_tagged(tag::snake)->attached_component<snake>();
}

void food_spawner::start()
{
    for (entity &wall : attached_to().find_all_tagged(tag::wall))
    {
        box_collider &collider = wall.attached_component<box_collider>();
        vector2 overlapped_area = 2.0F * collider.area();

        for (const auto &tile_center : _tile_maze->tiles_of_area(wall.transformation().position(), overlapped_area))
        {
            _wall_tiles.insert(tile_center);
        }
    }

    _tile_distribution = std::uniform_int_distribution<uint>(0, _tile_maze->tile_count() - 1);
    _remaining_food_count = _tile_maze->tile_count() - 1 - _wall_tiles.size() - snake_tiles().size();
    _messenger.send(game_start_requirement::food_spawner_ready);
}

void food_spawner::spawn()
{
    if (_remaining_food_count == 0)
    {
        _messenger.send(game_event::food_storage_depleted);
        return;
    }

    uint tile_index = _tile_distribution(_random_generator);
    uint i = 0;
    bool found = false;
    std::unordered_set<vector2> snake_positions = snake_tiles();

    while (!found && i < _tile_maze->tile_count())
    {
        ++tile_index;
        tile_index %= _tile_maze->tile_count();
        uint row = tile_index / _tile_maze->width();
        uint column = tile_index % _tile_maze->width();
        vector2 food_position = _tile_maze->tile_center(row, column);

        if (!_wall_tiles.contains(food_position) && !snake_positions.contains(food_position))
        {
            found = true;
            entity &food = entity::create();
            food.transformation().position(food_position);
            food.add_component<::food>(_tile_maze->tile_size());
            food.add_component<food_renderer>(render_layer::food, _tile_maze->tile_size());
            food.add_component<box_collider>(0.5F * vector2(_tile_maze->tile_size(), _tile_maze->tile_size()));
            food.attached_component<food_renderer>().change_material(material{color::food});
            --_remaining_food_count;
        }

        ++i;
    }
}

std::unordered_set<vector2> food_spawner::snake_tiles() const
{
    std::unordered_set<vector2> tiles;
    auto begin = _snake->segments().begin();
    auto end = ++_snake->segments().begin();

    while (end != _snake->segments().end())
    {
        vector2 segment = begin->points_to(*end);
        vector2 area = segment + 0.5F * _tile_maze->tile_size() * segment.normalize().perpendicular();
        vector2 center = *begin + 0.5F * segment;

        for (const auto &tile_center : _tile_maze->tiles_of_area(center, area))
        {
            tiles.insert(tile_center);
        }

        begin = end++;
    }

    return tiles;
}
