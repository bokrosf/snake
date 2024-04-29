#include <stdexcept>
#include <game/terrain/tile_renderer.h>

tile_renderer::tile_renderer(entity &attached_to, int layer_order, const tile_renderer_configuration &configuration)
    : renderer(attached_to, layer_order)
    , _configuration(configuration)
{
    if (configuration.tile_size < 0)
    {
        throw std::invalid_argument("Tile size must be greater than or equal to zero.");
    }
}

void tile_renderer::render(SDL_Renderer *renderer)
{
    if (!_material)
    {
        return;
    }
    
    SDL_Color &color = _material->color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
    vector2 start = _configuration.center - _configuration.bounds.absolute();
    vector2 end = _configuration.center + _configuration.bounds.absolute();
    int x_sections = (end.x() - start.x()) / _configuration.tile_size;
    int y_sections = (end.y() - start.y()) / _configuration.tile_size;

    for (int i = 0; i <= x_sections; ++i)
    {
        float x = start.x() + i * _configuration.tile_size;
        SDL_RenderDrawLineF(renderer, x, start.y(), x, end.y());
    }

    for (int i = 0; i <= y_sections; ++i)
    {
        float y = start.y() + i * _configuration.tile_size;
        SDL_RenderDrawLineF(renderer, start.x(), y, end.x(), y);
    }
}