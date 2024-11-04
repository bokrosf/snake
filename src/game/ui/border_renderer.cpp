#include <engine/entity.h>
#include <engine/vector2.h>
#include <game/ui/border_renderer.h>

border_renderer::border_renderer()
    : _border(nullptr)
{
}

void border_renderer::initialize()
{
    _border = &attached_to().attached_component<border>();
}

void border_renderer::render(SDL_Renderer *renderer)
{
    if (_border->thickness() <= 0 || !use_material_color(renderer))
    {
        return;
    }

    vector2 position = _border->transform().position() - _border->inner_area() - vector2(_border->thickness(), _border->thickness());
    SDL_FRect border_part;
    border_part.x = position.x;
    border_part.y = position.y;
    border_part.w = 2.0F * (_border->thickness() + _border->inner_area().x);
    border_part.h = _border->thickness();
    SDL_RenderFillRectF(renderer, &border_part);

    border_part.y = border_part.y + _border->thickness() + (2.0F * _border->inner_area().y);
    SDL_RenderFillRectF(renderer, &border_part);

    position = _border->transform().position() - _border->inner_area() - vector2(_border->thickness(), 0);
    border_part.x = position.x;
    border_part.y = position.y;
    border_part.w = _border->thickness();
    border_part.h = 2.0F * _border->inner_area().y;
    SDL_RenderFillRectF(renderer, &border_part);

    border_part.x = border_part.x + _border->thickness() + (2.0F * _border->inner_area().x);
    SDL_RenderFillRectF(renderer, &border_part);
}
