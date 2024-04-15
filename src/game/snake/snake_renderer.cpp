#include "snake_renderer.h"

snake_renderer::snake_renderer(game_object& attached_to, int layer_order, float thickness)
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
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    auto segment_start = _snake->segments().cbegin();
    auto segment_end = ++_snake->segments().cbegin();

    while (segment_end != _snake->segments().cend())
    {
        int half_thickness = _thickness / 2;
        vector2 offset = segment_start->points_to(*segment_end).normalize();
        offset *= half_thickness;
        draw_segment(renderer, *segment_start - offset, *segment_end + offset);
        segment_start = segment_end;
        ++segment_end;
    }
}

void snake_renderer::draw_segment(SDL_Renderer *renderer, const vector2 &start, const vector2 &end) const
{
    int half_thickness = _thickness / 2;
    vector2 perpendicular = start.points_to(end).perpendicular().normalize();

    for (int i = 0; i < half_thickness; ++i)
    {
        vector2 line_start = start - i * perpendicular;
        vector2 line_end = end - i * perpendicular;
        SDL_RenderDrawLine(renderer, line_start.x(), line_start.y(), line_end.x(), line_end.y());
        
        line_start = start + i * perpendicular;
        line_end = end + i * perpendicular;
        SDL_RenderDrawLine(renderer, line_start.x(), line_start.y(), line_end.x(), line_end.y());
    }
}
