#include <stdexcept>
#include <game/tile_maze/tile_maze_renderer.h>

tile_maze_renderer::tile_maze_renderer(entity &attached_to, int layer_order, const vector2 &bounds)
    : renderer(attached_to, layer_order)
    , _bounds(bounds)
{
}

void tile_maze_renderer::initialize()
{
    _maze = &attached_to().attached_component<tile_maze>();
}

void tile_maze_renderer::render(SDL_Renderer *renderer)
{
    if (!use_material_color(renderer))
    {
        return;
    }
    
    vector2 start = _maze->center() - _bounds.absolute();
    vector2 end = _maze->center() + _bounds.absolute();
    float tile_size = _maze->tile_size();
    int x_sections = (end.x() - start.x()) / tile_size;
    int y_sections = (end.y() - start.y()) / tile_size;

    for (int i = 0; i <= x_sections; ++i)
    {
        float x = start.x() + i * tile_size;
        SDL_RenderDrawLineF(renderer, x, start.y(), x, end.y());
    }

    for (int i = 0; i <= y_sections; ++i)
    {
        float y = start.y() + i * tile_size;
        SDL_RenderDrawLineF(renderer, start.x(), y, end.x(), y);
    }
}