#include <cmath>
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
        vector2 upper_left = wall.transformation().position() - collider.area();
        vector2 lower_right = wall.transformation().position() + collider.area();
        tile_area area = _tile_maze->tiles_of_area(upper_left, lower_right);

        for (int row = area.upper_left.y; row < area.lower_right.y; ++row)
        {
            for (int column = area.upper_left.x; column < area.lower_right.x; ++column)
            {
                _wall_tiles.insert(ivector2(column, row));
            }
        }
    }

    _tile_distribution = std::uniform_int_distribution<unsigned int>(0, _tile_maze->tile_count() - 1);
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

    unsigned int tile_index = _tile_distribution(_random_generator);
    unsigned int i = 0;
    bool found = false;
    std::unordered_set<ivector2> snake_positions = snake_tiles();

    while (!found && i < _tile_maze->tile_count())
    {
        ++tile_index;
        tile_index %= _tile_maze->tile_count();
        unsigned int row = tile_index / _tile_maze->width();
        unsigned int column = tile_index % _tile_maze->width();
        ivector2 food_position(column, row);

        if (!_wall_tiles.contains(food_position) && !snake_positions.contains(food_position))
        {
            found = true;
            const int nutritional_value = 1;
            entity &food = entity::create();
            food.transformation().position(_tile_maze->tile_center(food_position.y, food_position.x));
            food.add_component<::food>(nutritional_value);
            food.add_component<food_renderer>(render_layer::food, 0.75F *_tile_maze->tile_size());
            food.add_component<box_collider>(0.5F * vector2(_tile_maze->tile_size(), _tile_maze->tile_size()));
            food.attached_component<food_renderer>().change_material(material{color::food});
            --_remaining_food_count;
        }

        ++i;
    }
}

std::unordered_set<ivector2> food_spawner::snake_tiles() const
{
    std::unordered_set<ivector2> tiles;

    for (auto &segment : _snake->segments())
    {
        ivector2 direction = segment.direction_or(ivector2::right());
        unsigned int length = std::round(segment.begin.distance_from(segment.end));

        for (unsigned int i = 0; i <= length; ++i)
        {
            tiles.insert(segment.begin + i * direction);
        }
    }

    return tiles;
}
