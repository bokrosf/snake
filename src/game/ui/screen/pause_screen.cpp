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
    const int default_layer = 0;
    const int border_thickness = 10;
}

pause_screen::pause_screen(entity &attached_to)
    : behavior(attached_to)
    , _selected_item_index(static_cast<size_t>(menu_option::resume))
{
}

void pause_screen::initialize()
{
    entity &title = entity::create();
    title.attach_to(&attached_to());
    title.transformation().position(vector2(1920 / 2, 1080 / 4));
    image_renderer &title_renderer = title.add_component<image_renderer>(default_layer);
    title_renderer.change_material(material{.texture_path = asset_paths::pause_title_image});

    add_menu_item(menu_option::resume, asset_paths::resume_image);
    add_menu_item(menu_option::exit, asset_paths::exit_image);

    for (size_t i = 0; i < _menu_items.size(); ++i)
    {
        _menu_items[i]->transformation().translate(vector2(0, i * (128 + 4 * border_thickness)));
    }

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

void pause_screen::add_menu_item(menu_option option, const std::string &image_path)
{
    entity &item = entity::create();
    item.attach_to(&attached_to());
    
    border &border = item.add_component<::border>();
    border.transformation().position(0.5F * vector2(1920, 1080));
    border.inner_area(0.5F * vector2(256, 128));
    border.thickness(border_thickness);
    border_renderer &border_renderer = item.add_component<::border_renderer>(default_layer);
    border_renderer.activate(false);
    border_renderer.change_material({.color = SDL_Color(14, 209, 69, 255)});

    image_renderer &image_renderer = item.add_component<::image_renderer>(default_layer);
    image_renderer.change_material(material{.texture_path = image_path});

    _menu_items[static_cast<size_t>(option)] = &item;
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
            break;
    }
}

void pause_screen::resume()
{
    scene_navigator::instance().pop();
}
