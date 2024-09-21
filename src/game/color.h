#ifndef SNAKE_GAME_COLOR_H
#define SNAKE_GAME_COLOR_H

#include <SDL2/SDL.h>

namespace color
{
    const SDL_Color snake = SDL_Color{0, 255, 0, 255};
    const SDL_Color food = SDL_Color{255, 0, 0, 255};
    const SDL_Color wall = SDL_Color{128, 128, 128, 255};
    const SDL_Color tile_maze = SDL_Color{0, 0, 255, 255};
    const SDL_Color menu_item_border = SDL_Color{14, 209, 69, 255};
}

#endif
