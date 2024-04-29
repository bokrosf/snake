#include <engine/rendering/renderer.h>

renderer::renderer(entity &attached_to, int layer_order)
    : component(attached_to)
    , _layer_order(layer_order)
{
}

int renderer::layer_order() const
{
    return _layer_order;
}

void renderer::change_material(const ::material &material)
{
    _material.emplace(material);
}

bool renderer::use_material_color(SDL_Renderer *renderer)
{
    if (!_material)
    {
        return false;
    }

    const SDL_Color &color = _material->color;

    return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) == 0;
}
