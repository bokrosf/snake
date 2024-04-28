#include <game/terrain/tile_renderer.h>

tile_renderer::tile_renderer(entity &attached_to, int layer_order, float tile_size)
    : renderer(attached_to, layer_order)
    , _tile_size(tile_size)
{
}

void tile_renderer::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    for (int x = 0; x < 1920; x += _tile_size)
    {
        SDL_RenderDrawLine(renderer, x, 0, x, 1080);
    }

    for (int y = 0; y < 1080; y += _tile_size)
    {
        SDL_RenderDrawLine(renderer, 0, y, 1920, y);
    }
}