#ifndef SNAKE_GAME_COLOR_H
#define SNAKE_GAME_COLOR_H

#include <SDL2/SDL.h>

namespace color
{
    const SDL_Color snake_body = SDL_Color{0, 255, 0, 255};
    const SDL_Color snake_head = SDL_Color{255, 0, 0, 255};

    const SDL_Color wall = SDL_Color{128, 128, 128, 255};
    const SDL_Color tile_maze = SDL_Color{0, 0, 255, 255};
    const SDL_Color menu_item_border = SDL_Color{14, 209, 69, 255};

    const SDL_Color fantastic_durian = SDL_Color{184, 199, 1, 255};
    const SDL_Color furious_orange = SDL_Color{232, 120, 10, 255};
    const SDL_Color energetic_mango = SDL_Color{244, 187, 68, 255};
    const SDL_Color sassy_grape = SDL_Color{142, 45, 89, 255};
    const SDL_Color brave_strawberry = SDL_Color{152, 52, 45, 255};
    const SDL_Color elegant_kiwi = SDL_Color{97, 171, 90, 255};
}

#endif
