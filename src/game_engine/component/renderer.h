#ifndef SNAKE_GAMEENGINE_COMPONENT_RENDERER_H
#define SNAKE_GAMEENGINE_COMPONENT_RENDERER_H

#include <optional>
#include <SDL2/SDL.h>
#include "component.h"
#include "material.h"

class renderer : public component
{
public:
    virtual void render(SDL_Renderer *renderer) = 0;
    int layer_order() const;
    const std::optional<material> &material() const;
    void change_material(const ::material &material);
protected:
    std::optional<::material> _material;
    renderer(entity &attached_to, int layer_order);
private:
    const int _layer_order;
};

#endif
