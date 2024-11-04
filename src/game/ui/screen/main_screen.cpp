#include <engine/app_event.h>
#include <engine/display.h>
#include <engine/rendering/image_renderer.h>
#include <engine/rendering/material.h>
#include <game/assets/asset_path.h>
#include <game/scene/scene_navigator.h>
#include <game/scene/classic_scene.h>
#include <game/scene/magic_food_scene.h>
#include <game/ui/screen/main_screen.h>

namespace
{
    enum class menu_option
    {
        classic = 0,
        magic_food,
        exit
    };
}

main_screen::main_screen(const screen_configuration &configuration)
    : menu_screen(configuration)
{
}

void main_screen::initialize()
{
    SDL_DisplayMode display_mode = display::current_mode();

    entity &title = entity::create();
    title.attach_to(&attached_to());
    title.transform().position(vector2(display_mode.w / 2, display_mode.h / 4));
    image_renderer &title_renderer = title.add_component<image_renderer>();
    title_renderer.layer_order = _default_rendering_layer;
    title_renderer.material(material{.texture_path = asset_path::main_title_image});

    add_menu_item(asset_path::classic_image);
    add_menu_item(asset_path::magic_food_image);
    add_menu_item(asset_path::exit_image);

    select_item(static_cast<unsigned int>(menu_option::classic));
}

void main_screen::update()
{
    interact();
}

void main_screen::confirm()
{
    switch (static_cast<menu_option>(selected_item_index()))
    {
        case menu_option::classic:
            scene_navigator::instance().reset_root<classic_scene>();
            break;
        case menu_option::magic_food:
            scene_navigator::instance().reset_root<magic_food_scene>();
            break;
        case menu_option::exit:
            _messenger.send(app_event::exit_requested);
            break;
    }
}
