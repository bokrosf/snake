#include <game/ability/ability_indicator_renderer.h>

ability_indicator_renderer::ability_indicator_renderer(entity &attached_to, int layer_order)
    : renderer(attached_to, layer_order)
    , _indicator(nullptr)
{
}

void ability_indicator_renderer::initialize()
{
    _indicator = &attached_to().attached_component<ability_indicator>();
}

void ability_indicator_renderer::render(SDL_Renderer *renderer)
{
    if (!use_material_color(renderer))
    {
        return;
    }

    vector2 upper_left = transformation().position() - transformation().scale();
    vector2 area = 2.0F * transformation().scale();
    area.x *= _indicator->percentage();

    SDL_FRect rect
    {
        .x = upper_left.x,
        .y = upper_left.y,
        .w = area.x,
        .h = area.y
    };

    SDL_RenderFillRectF(renderer, &rect);
}
