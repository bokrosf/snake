#include <engine/collision/box_collider_renderer.h>

box_collider_renderer::box_collider_renderer(entity &attached_to, int layer_order)
    : renderer(attached_to, layer_order)
{
}

void box_collider_renderer::initialize()
{
    _collider = &attached_to().attached_component<box_collider>();
}

void box_collider_renderer::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 243, 255);
    
    vector2 start = _collider->transformation().position() + _collider->area();
    vector2 end = _collider->transformation().position() + vector2(-_collider->area().x(), _collider->area().y());
    SDL_RenderDrawLineF(renderer, start.x(), start.y(), end.x(), end.y());

    start = end;
    end = _collider->transformation().position() + vector2(-_collider->area().x(), -_collider->area().y());
    SDL_RenderDrawLineF(renderer, start.x(), start.y(), end.x(), end.y());
    
    start = end;
    end = _collider->transformation().position() + vector2(_collider->area().x(), -_collider->area().y());
    SDL_RenderDrawLineF(renderer, start.x(), start.y(), end.x(), end.y());
    
    start = end;
    end = _collider->transformation().position() + vector2(_collider->area().x(), _collider->area().y());
    SDL_RenderDrawLineF(renderer, start.x(), start.y(), end.x(), end.y());

    start = _collider->transformation().position();
    end = _collider->transformation().position() + _collider->area();
    SDL_RenderDrawLineF(renderer, start.x(), start.y(), end.x(), end.y());
}
