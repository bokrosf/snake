#include <engine/collision/box_collider.h>
#include <engine/collision/box_collider_renderer.h>
#include <engine/collision/collision_handler.h>
#include <engine/entity.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>
#include <game/scene/test_scene.h>
#include <game/snake/snake_controller.h>
#include <game/snake/snake_renderer.h>
#include <game/snake/tiled_movement_system.h>
#include <game/terrain/tile_renderer.h>
#include <game/wall/wall.h>
#include <game/wall/wall_renderer.h>

void test_scene::initialize()
{
    // Write logic to test.
    const float tile_size = 1920 / 30;
    const int terrain_layer = 0;
    const int wall_layer = terrain_layer + 1;
    const int food_layer = terrain_layer + 1;
    const int snake_layer = food_layer + 1;

    entity &terrain = entity::create();
    terrain.add_component<tile_renderer>(terrain_layer, tile_size);

    entity &snake = entity::create();
    snake.add_component<::snake>(vector2(5.5F * tile_size, 5.0F * tile_size), vector2(8.0F * tile_size, 5.0F * tile_size));
    snake.add_component<tiled_movement_system>(tile_size);
    snake.add_component<snake_renderer>(snake_layer, tile_size);
    snake.add_component<snake_controller>();
    snake.add_component<box_collider>(vector2(5.5F * tile_size, 5.0F * tile_size), vector2(5, 5));
    snake.add_component<box_collider_renderer>(99);
    snake.attached_component<::snake>().adjust_speed(50);
    snake.attached_component<snake_renderer>().change_material(material{SDL_Color{0, 255, 0, 255}});

    entity &food = entity::create();
    vector2 food_position = 8.5F * tile_size * vector2(1, 1);
    food.add_component<::food>(food_position, tile_size);
    food.add_component<food_renderer>(food_layer, tile_size);
    food.add_component<box_collider>(food_position, 0.5F * vector2(3 * tile_size, 6 * tile_size));
    food.add_component<box_collider_renderer>(99);
    food.attached_component<food_renderer>().change_material(material{SDL_Color{255, 0, 0, 255}});

    entity &wall = entity::create();
    wall.add_component<::wall>(tile_size * vector2(5, 12), vector2(10 * tile_size, tile_size));
    wall.add_component<wall_renderer>(wall_layer);
    wall.attached_component<wall_renderer>().change_material(material{SDL_Color{128, 128, 128, 255}});
}
