#include "renderer.h"

renderer::renderer(game_object &attached_to, int layer_order)
    : component(attached_to)
    , _layer_order(layer_order)
{
}

void renderer::initialize()
{
    _material = attached_to().find_component<material>();
}

int renderer::layer_order() const
{
    return _layer_order;
}
