#include <SDL2/SDL.h>
#include "snake_app.h"
#include "game/scene/test_scene.h"

snake_app::snake_app()
    : app("Snake SDL")
{
}

scene *snake_app::start()
{
    // TODO 2024-04-11 Instantiate classis_mode or game_mode_selector scene.
    return new test_scene();
}
