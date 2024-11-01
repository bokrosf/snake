#include <engine/display.h>
#include <engine/entity.h>
#include <engine/vector2.h>
#include <game/color.h>
#include <game/scene/pause_scene.h>
#include <game/ui/screen/pause_screen.h>
#include <game/ui/screen/screen_configuration.h>

pause_scene::pause_scene(int id)
    : scene(id)
{
}

void pause_scene::initialize()
{
    SDL_DisplayMode display_mode = display::current_mode();
    
    screen_configuration configuration
    {
        .border_thickness = display_mode.h * 10.0F / 1080.0F,
        .first_item_position = 0.5F * vector2(display_mode.w, display_mode.h),        
        .item_area = 0.5F * vector2(display_mode.w * (300.0F / 1080.0F), display_mode.h * (128.0F / 1080.0F)),
        .item_border_color = color::menu_item_border
    };

    configuration.item_spacing = display_mode.h * (128.0F / 1080.0F) + 4.0F * configuration.border_thickness;
    entity &screen = entity::create();
    screen.add_component<pause_screen>(configuration);
}
