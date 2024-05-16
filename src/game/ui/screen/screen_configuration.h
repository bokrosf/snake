#ifndef SNAKE_GAME_UI_SCREEN_SCREENCONFIGURATION_H
#define SNAKE_GAME_UI_SCREEN_SCREENCONFIGURATION_H

#include <SDL2/SDL.h>
#include <engine/vector2.h>

struct screen_configuration
{
    float border_thickness;
    vector2 first_item_position;
    float item_spacing;
    vector2 item_area;
    SDL_Color item_border_color;
};

#endif
