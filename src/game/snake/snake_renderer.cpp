#include <game/snake/snake_renderer.h>

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
    if (!use_material_color(renderer))
    {
        return;
    }
    
    auto begin = _snake->segments().cbegin();
    auto end = ++_snake->segments().cbegin();

    draw_segment(renderer, *begin, *end);
    begin = end++;

    while (end != _snake->segments().cend())
    {
        vector2 offset = (half_thickness() - 1) * begin->points_to(*end).normalize();
        draw_segment(renderer, *begin - offset, *end);
        begin = end++;
    }
}

void snake_renderer::draw_segment(SDL_Renderer *renderer, const vector2 &begin, const vector2 &end) const
{
    vector2 perpendicular = begin.points_to(end).perpendicular().normalize();

    for (int i = 0; i < half_thickness(); ++i)
    {
        vector2 line_begin = begin - i * perpendicular;
        vector2 line_end = end - i * perpendicular;
        SDL_RenderDrawLine(renderer, line_begin.x(), line_begin.y(), line_end.x(), line_end.y());
        
        line_begin = begin + i * perpendicular;
        line_end = end + i * perpendicular;
        SDL_RenderDrawLine(renderer, line_begin.x(), line_begin.y(), line_end.x(), line_end.y());
    }
}

int snake_renderer::half_thickness() const
{
    return _thickness / 2;
}
