#include "test_scene.h"
#include <game_engine/game_object.h>
#include <game/snake/snake_renderer.h>
#include <game/snake/tiled_movement_system.h>
#include <game/snake/snake_controller.h>
#include <game/terrain/tile_renderer.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>

class test_food : public food
{
public:
    test_food(game_object &attached_to, const vector2 &position)
        : food(attached_to, position)
    {
    }

    void update() override
    {

    }

    void eat(snake &snake) override
    {
    }
};

void test_scene::initialize()
{
    // Write logic to test.
    const float tile_size = 1920 / 30;
    const int terrain_layer = 0;
    const int food_layer = terrain_layer + 1;
    const int snake_layer = food_layer + 1;

    game_object &terrain = game_object::create();
    terrain.add_component<tile_renderer>(terrain_layer, tile_size);

    game_object &snake = game_object::create();
    snake.add_component<::snake>(vector2(500, 300), vector2(1300, 300));
    snake.add_component<tiled_movement_system>(tile_size);
    snake.add_component<snake_renderer>(snake_layer, tile_size);
    snake.add_component<snake_controller>();
    snake.attached_component<::snake>().change_speed(50);
    snake.attached_component<snake_renderer>().change_material(material{SDL_Color{0, 255, 0, 255}});

    game_object &food = game_object::create();
    vector2 food_position = 8.5F * tile_size * vector2(1, 1);
    food.add_component<::test_food>(food_position);
    food.add_component<food_renderer>(food_layer, tile_size);
    food.attached_component<food_renderer>().change_material(material{SDL_Color{255, 0, 0, 255}});
}
