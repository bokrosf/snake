#include "snake_renderer.h"

snake_renderer::snake_renderer(entity& attached_to, int layer_order, float thickness)
    : renderer(attached_to, layer_order)
    , _snake(nullptr)
    , _thickness(thickness)
{
}

void snake_renderer::initialize()
{
    _snake = &attached_to().attached_component<snake>();
}

void snake_renderer::render(SDL_Renderer *renderer)
{    
    if (!_material)
    {
        return;
    }
    
    const SDL_Color &color = _material->color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    auto segment_start = _snake->segments().cbegin();
    auto segment_end = ++_snake->segments().cbegin();

    draw_segment(renderer, *segment_start, *segment_end);
    segment_start = segment_end++;

    while (segment_end != _snake->segments().cend())
    {
        vector2 offset = (half_thickness() - 1) * segment_start->points_to(*segment_end).normalize();
        draw_segment(renderer, *segment_start - offset, *segment_end);
        segment_start = segment_end++;
    }
}

void snake_renderer::draw_segment(SDL_Renderer *renderer, const vector2 &start, const vector2 &end) const
{
    vector2 perpendicular = start.points_to(end).perpendicular().normalize();

    for (int i = 0; i < half_thickness(); ++i)
    {
        vector2 line_start = start - i * perpendicular;
        vector2 line_end = end - i * perpendicular;
        SDL_RenderDrawLine(renderer, line_start.x(), line_start.y(), line_end.x(), line_end.y());
        
        line_start = start + i * perpendicular;
        line_end = end + i * perpendicular;
        SDL_RenderDrawLine(renderer, line_start.x(), line_start.y(), line_end.x(), line_end.y());
    }
}

int snake_renderer::half_thickness() const
{
    return _thickness / 2;
}
