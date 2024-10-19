#include <game/food/food_renderer.h>

food_renderer::food_renderer(entity &attached_to, int layer_order)
    : renderer(attached_to, layer_order)
{
}

void food_renderer::render(SDL_Renderer *renderer)
{
    if (!use_material_color(renderer))
    {
        return;
    }

    vector2 upper_left = transformation().position() - transformation().scale();
    vector2 area = 2.0F * transformation().scale();

    SDL_FRect rect
    {
        .x = upper_left.x,
        .y = upper_left.y,
        .w = area.x,
        .h = area.y
    };

    SDL_RenderFillRectF(renderer, &rect);
}
