#include <stdexcept>
#include "food_renderer.h"

food_renderer::food_renderer(game_object &attached_to, int layer_order, float thickness)
    : renderer(attached_to, layer_order)
    , _thickness(thickness)
    , _food(nullptr)
{
    if (thickness <= 0)
    {
        throw std::invalid_argument("Thickness must be greater than zero.");
    }
}

void food_renderer::initialize()
{
    _food = &attached_to().attached_component<food>();
}

void food_renderer::render(SDL_Renderer *renderer)
{
    if (!_material)
    {
        return;
    }

    const SDL_Color &color = _material->color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    float half_thickness = 0.5F * _thickness;
    vector2 draw_position = _food->position() - vector2(half_thickness - 1, half_thickness - 1);
    SDL_FRect rect;
    rect.x = draw_position.x();
    rect.y = draw_position.y();
    rect.w = _thickness - 1;
    rect.h = _thickness - 1;
    SDL_RenderFillRectF(renderer, &rect);
}
