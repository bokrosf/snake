#include <game/scene/classic_scene.h>
#include <game/scene/scene_navigator.h>
#include <game/snake_app.h>

snake_app::snake_app(const app_configuration &configuration)
    : app(configuration)
{
}

snake_app::~snake_app()
{
    scene_navigator::shutdown();
}

void snake_app::load_start_scene(scene_loader &loader)
{
    scene_navigator::initialize(loader);
    scene_navigator::instance().push<classic_scene>();
}
