#include <game/scene/classic_scene.h>
#include <game/snake_app.h>

snake_app::snake_app(const app_configuration &configuration)
    : app(configuration)
{
}

scene *snake_app::create_start_scene()
{
    // TODO 2024-04-11 Instantiate game_mode_selector scene.
    return new classic_scene();
}
