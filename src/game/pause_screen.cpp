#include <engine/input.h>
#include <game/pause_screen.h>
#include <game/scene/scene_navigator.h>

pause_screen::pause_screen(entity &attached_to)
    : behavior(attached_to)
{
}

void pause_screen::update()
{
    if (input::key_down(SDLK_ESCAPE) || input::key_down(SDLK_p))
    {
        scene_navigator::instance().pop();
    }
}
