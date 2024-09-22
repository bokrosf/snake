#include <stdexcept>
#include <game/food/food_renderer.h>

food_renderer::food_renderer(entity &attached_to, int layer_order, float thickness)
    : renderer(attached_to, layer_order)
    , _thickness(thickness)
    , _food(nullptr)
{
    if (thickness < 0)
    {
        throw std::invalid_argument("Thickness must be greater than or equal to zero.");
    }
}

void food_renderer::initialize()
{
    _food = &attached_to().attached_component<food>();
}

void food_renderer::render(SDL_Renderer *renderer)
{
    if (!use_material_color(renderer))
    {
        return;
    }

    float half_thickness = 0.5F * _thickness;
    vector2 draw_position = _food->transformation().position() - vector2(half_thickness - 1, half_thickness - 1);
    SDL_FRect rect;
    rect.x = draw_position.x;
    rect.y = draw_position.y;
    rect.w = _thickness;
    rect.h = _thickness;
    SDL_RenderFillRectF(renderer, &rect);
}
