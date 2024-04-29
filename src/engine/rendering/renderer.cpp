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
