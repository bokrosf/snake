#include <engine/app_event.h>
#include <engine/display.h>
#include <engine/input.h>
#include <engine/rendering/image_renderer.h>
#include <engine/rendering/material.h>
#include <game/assets/asset_path.h>
#include <game/ui/screen/pause_screen.h>
#include <game/scene/main_scene.h>
#include <game/scene/scene_navigator.h>

namespace
{
    enum class menu_option
    {
        resume = 0,
        main_menu,
        exit
    };
}

pause_screen::pause_screen(entity &attached_to, const screen_configuration &configuration)
    : menu_screen(attached_to, configuration)
{
}

void pause_screen::initialize()
{
    SDL_DisplayMode display_mode = display::current_mode();

    entity &title = entity::create();
    title.attach_to(&attached_to());
    title.transform().position(vector2(display_mode.w / 2, display_mode.h / 4));
    image_renderer &title_renderer = title.add_component<image_renderer>(_default_rendering_layer);
    title_renderer.material(material{.texture_path = asset_path::pause_title_image});

    add_menu_item(asset_path::resume_image);
    add_menu_item(asset_path::main_menu_image);
    add_menu_item(asset_path::exit_image);

    select_item(static_cast<unsigned int>(menu_option::resume));
}

void pause_screen::update()
{
    if (input::key_down(SDLK_ESCAPE) || input::key_down(SDLK_p))
    {
        resume();
    }
    else
    {
        interact();
    }
}

void pause_screen::confirm()
{
    switch (static_cast<menu_option>(selected_item_index()))
    {
        case menu_option::resume:
            resume();
            break;
        case menu_option::main_menu:
            scene_navigator::instance().reset_root<main_scene>();
            break;
        case menu_option::exit:
            _messenger.send(app_event::exit_requested);
            break;
    }
}

void pause_screen::resume()
{
    scene_navigator::instance().pop();
}
