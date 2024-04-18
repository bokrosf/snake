#include "test_scene.h"
#include <game_engine/game_object.h>
#include "../snake/snake_renderer.h"
#include "../snake/tiled_movement_system.h"
#include "../snake/snake_controller.h"
#include "../terrain/tile_renderer.h"

void test_scene::initialize()
{
    // Write logic to test.
    const float tile_size = 1920 / 30;

    game_object &terrain = game_object::create();
    terrain.add_component<tile_renderer>(0, tile_size);

    game_object &snake = game_object::create();
    snake.add_component<::snake>(vector2(500, 300), vector2(1300, 300));
    snake.add_component<tiled_movement_system>(tile_size);
    snake.add_component<snake_renderer>(2, tile_size);
    snake.add_component<snake_controller>();
    snake.attached_component<::snake>().change_speed(50);
    snake.attached_component<snake_renderer>().change_material(material{SDL_Color{0, 255, 0, 255}});
}
