#include <engine/app_event.h>
#include <engine/display.h>
#include <engine/entity.h>
#include <engine/rendering/image_renderer.h>
#include <engine/rendering/material.h>
#include <game/assets/asset_path.h>
#include <game/scene/main_scene.h>
#include <game/scene/scene_navigator.h>
#include <game/ui/screen/game_ending_screen.h>

namespace
{
    enum class menu_option
    {
        restart = 0,
        main_menu,
        exit
    };
}

game_ending_screen::game_ending_screen(const screen_configuration &configuration, bool won)
    : menu_screen(configuration)
    , _won(won)
{
}

void game_ending_screen::initialize()
{
    SDL_DisplayMode display_mode = display::current_mode();
    
    entity &title = entity::create();
    title.attach_to(&attached_to());
    title.transform().position(vector2(display_mode.w / 2, display_mode.h / 4));
    image_renderer &title_renderer = title.add_component<image_renderer>();
    title_renderer.layer_order = _default_rendering_layer;
    title_renderer.material(material{.texture_path = _won ? asset_path::game_won_title : asset_path::game_lost_title});

    add_menu_item(asset_path::restart_image);
    add_menu_item(asset_path::main_menu_image);
    add_menu_item(asset_path::exit_image);

    select_item(static_cast<unsigned int>(menu_option::restart));
}

void game_ending_screen::update()
{
    interact();
}

void game_ending_screen::confirm()
{
    switch (static_cast<menu_option>(selected_item_index()))
    {
        case menu_option::restart:
            scene_navigator::instance().pop();
            scene_navigator::instance().reset_top();
            break;
        case menu_option::main_menu:
            scene_navigator::instance().reset_root<main_scene>();
            break;
        case menu_option::exit:
            _messenger.send(app_event::exit_requested);
            break;
    }
}
