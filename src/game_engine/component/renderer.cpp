#include <game_engine/component/renderer.h>

renderer::renderer(entity &attached_to, int layer_order)
    : component(attached_to)
    , _layer_order(layer_order)
{
}

int renderer::layer_order() const
{
    return _layer_order;
}

const std::optional<material> &renderer::material() const
{
    return _material;
}

void renderer::change_material(const ::material &material)
{
    _material.emplace(material);
}
