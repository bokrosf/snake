#ifndef SNAKE_GAMEENGINE_COMPONENT_RENDERER_H
#define SNAKE_GAMEENGINE_COMPONENT_RENDERER_H

#include <SDL2/SDL.h>
#include "component.h"
#include "material.h"

class renderer : public component
{
public:
    void initialize() override;
    virtual void render(SDL_Renderer *renderer) = 0;
    int layer_order() const;
protected:
    renderer(game_object &attached_to, int layer_order);
    const material *_material;
private:
    const int _layer_order;
};

#endif
