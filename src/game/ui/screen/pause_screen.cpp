#include <engine/app_event.h>
#include <engine/display.h>
#include <engine/input.h>
#include <engine/rendering/image_renderer.h>
#include <engine/rendering/material.h>
#include <engine/vector2.h>
#include <game/assets/asset_paths.h>
#include <game/ui/border.h>
#include <game/ui/border_renderer.h>
#include <game/ui/screen/pause_screen.h>
#include <game/scene/scene_navigator.h>

namespace
{
    enum class menu_option
    {
        resume = 0,
        exit
    };
    
    const int default_layer = 0;
}

pause_screen::pause_screen(entity &attached_to, const screen_configuration &configuration)
    : behavior(attached_to)
    , _configuration(configuration)
    , _selected_item_index(static_cast<size_t>(menu_option::resume))
{
}

void pause_screen::initialize()
{
    SDL_DisplayMode display_mode = display::current_mode();

    entity &title = entity::create();
    title.attach_to(&attached_to());
    title.transformation().position(vector2(display_mode.w / 2, display_mode.h / 4));
    image_renderer &title_renderer = title.add_component<image_renderer>(default_layer);
    title_renderer.change_material(material{.texture_path = asset_paths::pause_title_image});

    add_menu_item(asset_paths::resume_image);
    add_menu_item(asset_paths::exit_image);

    select_item(static_cast<size_t>(menu_option::resume));
}

void pause_screen::update()
{
    if (input::key_down(SDLK_ESCAPE) || input::key_down(SDLK_p))
    {
        resume();
    }
    else if (input::key_down(SDLK_UP))
    {
        select_item(_selected_item_index + 1);
    }
    else if (input::key_down(SDLK_DOWN))
    {
        select_item(_selected_item_index - 1);
    }
    else if (input::key_down(SDLK_RETURN) || input::key_down(SDLK_SPACE))
    {
        confirm();
    }
}

void pause_screen::add_menu_item(const std::string &image_path)
{
    entity &item = entity::create();
    item.attach_to(&attached_to());
    
    border &border = item.add_component<::border>();
    border.transformation().position(_configuration.first_item_position + vector2(0, _menu_items.size() * _configuration.item_spacing));
    border.inner_area(_configuration.item_area);
    border.thickness(_configuration.border_thickness);
    border_renderer &border_renderer = item.add_component<::border_renderer>(default_layer);
    border_renderer.activate(false);
    border_renderer.change_material({.color = _configuration.item_border_color});

    image_renderer &image_renderer = item.add_component<::image_renderer>(default_layer);
    image_renderer.change_material(material{.texture_path = image_path});

    _menu_items.push_back(&item);
}

void pause_screen::select_item(size_t index)
{
    _menu_items[_selected_item_index]->attached_component<border_renderer>().activate(false);
    index %= _menu_items.size();
    _menu_items[index]->attached_component<border_renderer>().activate(true);
    _selected_item_index = index;
}

void pause_screen::confirm()
{
    switch (static_cast<menu_option>(_selected_item_index))
    {
        case menu_option::resume:
            resume();
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
