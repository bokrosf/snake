#ifndef SNAKE_GAMEENGINE_COMPONENT_RENDERER_H
#define SNAKE_GAMEENGINE_COMPONENT_RENDERER_H

#include <SDL2/SDL.h>
#include "component.h"

class renderer : public component
{
public:
    virtual void render(SDL_Renderer *renderer) = 0;
protected:
    renderer(game_object &attached_to);
};

#endif
