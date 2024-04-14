#include "test_scene.h"
#include <game_engine/game_object.h>
#include "../snake/snake_renderer.h"
#include "../snake/tiled_movement_system.h"

void test_scene::initialize()
{
    // Write logic to test.
    game_object *snake = new game_object();
    snake->add_component<::snake>(vector2(500, 300), vector2(1300, 300));
    snake->add_component<tiled_movement_system>(70);
    snake->add_component<snake_renderer>(2, 50);
    update_root_status(*snake);
}
