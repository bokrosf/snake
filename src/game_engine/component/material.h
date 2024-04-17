#ifndef SNAKE_GAMEENGINE_COMPONENT_MATERIAL_H
#define SNAKE_GAMEENGINE_COMPONENT_MATERIAL_H

#include <SDL2/SDL.h>
#include "component.h"

class material : public component
{
public:
    material(game_object &attached_to);
    const SDL_Color &color() const;
    void change_color(const SDL_Color &color);
private:
    SDL_Color _color;
};

#endif
