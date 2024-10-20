#include <game/wall/wall_renderer.h>

wall_renderer::wall_renderer(entity &attached_to, int layer_order)
    : renderer(attached_to, layer_order)
{
}

void wall_renderer::render(SDL_Renderer *renderer)
{
    if (!use_material_color(renderer))
    {
        return;
    }

    vector2 upper_left = transform().position() - transform().scale();
    vector2 area = 2.0F * transform().scale();

    SDL_FRect rect
    {
        .x = upper_left.x,
        .y = upper_left.y,
        .w = area.x,
        .h = area.y
    };

    SDL_RenderFillRectF(renderer, &rect);
}
