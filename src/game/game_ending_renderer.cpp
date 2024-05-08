#include <game/game_ending_renderer.h>

game_ending_renderer::game_ending_renderer(entity &attached_to, int layer_order)
    : renderer(attached_to, layer_order)
{
}

void game_ending_renderer::render(SDL_Renderer *renderer)
{
    if (!use_material_color(renderer))
    {
        return;
    }

    SDL_RenderClear(renderer);
}
