#ifndef SNAKE_ENGINE_INPUT_H
#define SNAKE_ENGINE_INPUT_H

#include <vector>
#include <SDL2/SDL.h>

namespace input
{
    void update_events(std::vector<SDL_Event> &&events);
    bool key_down(SDL_KeyCode key);
}

#endif
