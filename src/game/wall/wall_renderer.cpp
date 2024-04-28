#include "wall_renderer.h"

wall_renderer::wall_renderer(entity &attached_to, int layer_order)
    : renderer(attached_to, layer_order)
{
}

void wall_renderer::initialize()
{
    _wall = &attached_to().attached_component<wall>();
}

void wall_renderer::render(SDL_Renderer *renderer)
{
    if (!_material)
    {
        return;
    }

    SDL_Color &color = _material->color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_FRect rect;
    rect.x = _wall->position().x();
    rect.y = _wall->position().y();
    rect.w = _wall->area().x();
    rect.h = _wall->area().y();

    SDL_RenderFillRectF(renderer, &rect);
}
