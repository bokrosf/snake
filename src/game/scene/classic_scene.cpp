#include <SDL2/SDL.h>
#include <engine/collision/box_collider.h>
#include <engine/collision/box_collider_renderer.h>
#include <engine/collision/collision_handler.h>
#include <engine/display.h>
#include <engine/entity.h>
#include <game/color.h>
#include <game/entity_name.h>
#include <game/fatal_collision_handler.h>
#include <game/food/food_spawner.h>
#include <game/game_coordinator.h>
#include <game/render_layer.h>
#include <game/scene/classic_scene.h>
#include <game/snake/snake_controller.h>
#include <game/snake/snake_renderer.h>
#include <game/tag.h>
#include <game/tile_maze/tile_maze.h>
#include <game/tile_maze/tile_maze_renderer.h>
#include <game/wall/wall_renderer.h>

namespace
{
    void create_wall(const vector2 &position, const vector2 &area)
    {
        entity &wall = entity::create();
        wall.tag(tag::wall);
        wall.transform().position(position);
        wall.transform().scale(area);
        wall.add_component<wall_renderer>().layer_order = render_layer::wall;
        wall.add_component<box_collider>(area);
        wall.add_component<box_collider_renderer>().layer_order = render_layer::collider;
        wall.add_component<fatal_collision_handler>();
        wall.attached_component<wall_renderer>().material(material{color::wall});
    }
}

classic_scene::classic_scene(int id)
    : scene(id)
{
}

void classic_scene::initialize()
{
    const SDL_DisplayMode &display_mode = display::current_mode();
    const int horizontal_tile_count = 19;
    const int vertical_tile_count = 11;
    const float tile_size = display_mode.w / 30;
    const unsigned int snake_length = 3;

    entity &map = entity::create(entity_name::map);
    tile_maze &maze = map.add_component<tile_maze>(tile_size, horizontal_tile_count, vertical_tile_count);
    maze.transform().position(0.5F * vector2(display_mode.w, display_mode.h));
    vector2 tile_maze_rendering_bounds = 0.5F * vector2(horizontal_tile_count * tile_size, vertical_tile_count * tile_size);
    map.add_component<tile_maze_renderer>(tile_maze_rendering_bounds).layer_order = render_layer::terrain;
    map.attached_component<tile_maze_renderer>().material(material{color::tile_maze});

    entity &snake = entity::create(entity_name::snake);

    tile_area snake_area = maze.tiles_of_area(
        maze.transform().position(),
        maze.transform().position() + vector2((snake_length - 1) * tile_size, 0));

    snake.add_component<::snake>(snake_area.upper_left, snake_area.lower_right);
    snake.add_component<snake_renderer>().layer_order = render_layer::snake;
    snake.add_component<snake_controller>();
    snake.add_component<box_collider>(0.5F * vector2(tile_size, tile_size));
    snake.add_component<box_collider_renderer>().layer_order = render_layer::collider;
    snake.attached_component<::snake>().speed(4);
    snake.attached_component<snake_renderer>().material(material{color::snake});

    entity &coordinator = entity::create();
    coordinator.add_component<game_coordinator>();
    coordinator.add_component<food_spawner>(_food_factory);

    const float half_tile_size = 0.5F * maze.tile_size();
    
    create_wall(
        maze.transform().position() - 0.5F * tile_size * vector2(0, vertical_tile_count) + vector2(0, half_tile_size),
        vector2(0.5F * horizontal_tile_count * tile_size, 0.5F * tile_size));

    create_wall(
        maze.transform().position() + 0.5F * tile_size * vector2(0, vertical_tile_count) - vector2(0, half_tile_size),
        vector2(0.5F * horizontal_tile_count * tile_size, 0.5F * tile_size));

    create_wall(
        maze.transform().position() - 0.5F * tile_size * vector2(horizontal_tile_count, 0) + vector2(half_tile_size, 0),
        vector2(0.5F * tile_size, 0.5F * (vertical_tile_count - 2) * tile_size));

    create_wall(
        maze.transform().position() + 0.5F * tile_size * vector2(horizontal_tile_count, 0) - vector2(half_tile_size, 0),
        vector2(0.5F * tile_size, 0.5F * (vertical_tile_count - 2) * tile_size));
}
