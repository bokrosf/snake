#include <SDL2/SDL.h>
#include <engine/collision/box_collider.h>
#include <engine/collision/box_collider_renderer.h>
#include <engine/collision/collision_handler.h>
#include <engine/display.h>
#include <engine/entity.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>
#include <game/scene/classic_scene.h>
#include <game/snake/snake_controller.h>
#include <game/snake/snake_renderer.h>
#include <game/snake/tiled_movement_system.h>
#include <game/terrain/tile_renderer.h>
#include <game/tile_maze.h>
#include <game/wall/wall.h>
#include <game/wall/wall_renderer.h>

namespace
{
    const int collider_layer = 99;
    const int terrain_layer = 0;
    const int wall_layer = terrain_layer + 1;
    const int food_layer = terrain_layer + 1;
    const int snake_layer = food_layer + 1;

    void create_wall(const vector2 &position, const vector2 &area)
    {
        entity &wall = entity::create();
        wall.add_component<::wall>(position, area);
        wall.add_component<wall_renderer>(wall_layer);
        wall.add_component<box_collider>(position + 0.5F * area, 0.5F * area);
        wall.add_component<box_collider_renderer>(collider_layer);
        wall.attached_component<wall_renderer>().change_material(material{SDL_Color{128, 128, 128, 255}});
    }
}


void classic_scene::initialize()
{
    // Write logic to test.
    const SDL_DisplayMode &display_mode = display::current_mode();
    const int horizontal_tile_count = 19;
    const int vertical_tile_count = 11;
    const float tile_size = display_mode.w / 30;

    entity &map = entity::create();
    tile_maze &maze = map.add_component<tile_maze>(0.5F * vector2(display_mode.w, display_mode.h), tile_size);

    tile_renderer_configuration tile_renderer_configuration
    {
        .tile_size = tile_size,
        .center = maze.center(),
        .bounds = 0.5F * vector2(horizontal_tile_count * tile_size, vertical_tile_count * tile_size)
    };

    map.add_component<tile_renderer>(terrain_layer, tile_renderer_configuration);
    map.attached_component<tile_renderer>().change_material(material{SDL_Color{0, 0, 255, 255}});

    entity &snake = entity::create();
    snake.add_component<::snake>(maze.center(), maze.tile_center(maze.center() + vector2(3.0F * tile_size, 0)));
    snake.add_component<tile_maze>(maze.center(), maze.tile_size());
    snake.add_component<tiled_movement_system>();
    snake.add_component<snake_renderer>(snake_layer, tile_size);
    snake.add_component<snake_controller>();
    snake.add_component<box_collider>(maze.center(), vector2(5, 5));
    snake.add_component<box_collider_renderer>(collider_layer);
    snake.attached_component<::snake>().adjust_speed(50);
    snake.attached_component<snake_renderer>().change_material(material{SDL_Color{0, 255, 0, 255}});

    entity &food = entity::create();
    const vector2 food_position = maze.tile_center(maze.center() + vector2(-3.0F * tile_size, 4.0F * tile_size));
    food.add_component<::food>(food_position, tile_size);
    food.add_component<food_renderer>(food_layer, tile_size);
    food.add_component<box_collider>(food_position, 0.5F * vector2(3 * tile_size, 6 * tile_size));
    food.add_component<box_collider_renderer>(99);
    food.attached_component<food_renderer>().change_material(material{SDL_Color{255, 0, 0, 255}});

    create_wall(maze.center() + vector2(-0.5F * horizontal_tile_count * tile_size, -0.5F * vertical_tile_count * tile_size), vector2(horizontal_tile_count * tile_size, tile_size));
    create_wall(maze.center() + vector2(-0.5F * horizontal_tile_count * tile_size, 0.5F * (vertical_tile_count - 2) * tile_size), vector2(horizontal_tile_count * tile_size, tile_size));
    create_wall(maze.center() + vector2(-0.5F * horizontal_tile_count * tile_size, -0.5F * (vertical_tile_count - 2) * tile_size), vector2(tile_size, (vertical_tile_count - 2) * tile_size));
    create_wall(maze.center() + vector2(0.5F * (horizontal_tile_count - 2) * tile_size, -0.5F * (vertical_tile_count - 2) * tile_size), vector2(tile_size, (vertical_tile_count - 2) * tile_size));
}