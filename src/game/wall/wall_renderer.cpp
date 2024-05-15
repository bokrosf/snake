#include <game/wall/wall_renderer.h>

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
    if (!use_material_color(renderer))
    {
        return;
    }

    vector2 rect_position = _wall->transformation().position() - _wall->area();
    SDL_FRect rect;
    rect.x = rect_position.x();
    rect.y = rect_position.y();
    rect.w = 2.0F * _wall->area().x();
    rect.h = 2.0F * _wall->area().y();

    SDL_RenderFillRectF(renderer, &rect);
}
