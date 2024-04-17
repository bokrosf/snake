#include "material.h"

material::material(game_object &attached_to)
    : component(attached_to)
{
}

const SDL_Color &material::color() const
{
    return _color;
}

void material::change_color(const SDL_Color &color)
{
    _color = color;
}
