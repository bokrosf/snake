#include <stdexcept>
#include <game/tile_maze/tile_maze_renderer.h>

tile_maze_renderer::tile_maze_renderer(entity &attached_to, const vector2 &bounds)
    : renderer(attached_to)
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
    
    vector2 begin = _maze->transform().position() - _bounds.absolute();
    vector2 end = _maze->transform().position() + _bounds.absolute();
    float tile_size = _maze->tile_size();
    int x_sections = (end.x - begin.x) / tile_size;
    int y_sections = (end.y - begin.y) / tile_size;

    for (int i = 0; i <= x_sections; ++i)
    {
        float x = begin.x + i * tile_size;
        SDL_RenderDrawLineF(renderer, x, begin.y, x, end.y);
    }

    for (int i = 0; i <= y_sections; ++i)
    {
        float y = begin.y + i * tile_size;
        SDL_RenderDrawLineF(renderer, begin.x, y, end.x, y);
    }
}