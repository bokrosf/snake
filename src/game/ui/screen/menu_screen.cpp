#include <engine/input.h>
#include <engine/rendering/image_renderer.h>
#include <engine/rendering/material.h>
#include <engine/vector2.h>
#include <game/ui/border.h>
#include <game/ui/border_renderer.h>
#include <game/ui/screen/menu_screen.h>

menu_screen::menu_screen(entity &attached_to, const screen_configuration &configuration)
    : behavior(attached_to)
    , _configuration(configuration)
    , _default_rendering_layer(0)
    , _selected_item_index(0)
{
}

void menu_screen::add_menu_item(const std::string &image_path)
{
    entity &item = entity::create();
    item.attach_to(&attached_to());
    
    border &border = item.add_component<::border>();
    border.transform().position(_configuration.first_item_position + vector2(0, _menu_items.size() * _configuration.item_spacing));
    border.inner_area(_configuration.item_area);
    border.thickness(_configuration.border_thickness);
    border_renderer &border_renderer = item.add_component<::border_renderer>(_default_rendering_layer);
    border_renderer.activate(false);
    border_renderer.material({.color = _configuration.item_border_color});

    image_renderer &image_renderer = item.add_component<::image_renderer>(_default_rendering_layer);
    image_renderer.material(material{.texture_path = image_path});

    _menu_items.push_back(&item);
}

unsigned int menu_screen::selected_item_index() const
{
    return _selected_item_index;
}

void menu_screen::select_item(unsigned int index)
{
    _menu_items[_selected_item_index]->attached_component<border_renderer>().activate(false);
    index %= _menu_items.size();
    _menu_items[index]->attached_component<border_renderer>().activate(true);
    _selected_item_index = index;
}

void menu_screen::interact()
{
    if (input::key_down(SDLK_UP))
    {
        select_item(_selected_item_index > 0 ? _selected_item_index - 1 : _menu_items.size() - 1);
    }
    else if (input::key_down(SDLK_DOWN))
    {
        select_item(_selected_item_index + 1);
    }
    else if (input::key_down(SDLK_RETURN) || input::key_down(SDLK_SPACE))
    {
        confirm();
    }
}
