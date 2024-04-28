#ifndef SNAKE_ENGINE_DISPLAY_H
#define SNAKE_ENGINE_DISPLAY_H

#include <SDL2/SDL.h>

namespace display
{
    void initialize();
    SDL_DisplayMode current_mode();
}

#endif
