#include <SDL2/SDL.h>
#include <game/scene/test_scene.h>
#include <game/snake_app.h>

snake_app::snake_app(const app_configuration &configuration)
    : app(configuration)
{
}

scene *snake_app::create_start_scene()
{
    // TODO 2024-04-11 Instantiate classis_mode or game_mode_selector scene.
    return new test_scene();
}
