#include <engine/entity.h>
#include <game/wall/wall_renderer.h>

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
