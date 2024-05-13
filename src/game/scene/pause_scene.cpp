#include <engine/entity.h>
#include <game/scene/pause_scene.h>
#include <game/pause_screen.h>

void pause_scene::initialize()
{
    entity &screen = entity::create();
    screen.add_component<pause_screen>();
}
