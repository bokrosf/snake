#ifndef ENGINE_RENDERING_RENDERER_H
#define ENGINE_RENDERING_RENDERER_H

#include <optional>
#include <SDL2/SDL.h>
#include <engine/component/behavior.h>
#include <engine/rendering/material.h>

class renderer : public behavior
{
public:
    virtual void render(SDL_Renderer *renderer) = 0;
    ::material *material();
    void material(const ::material &material);
    
    int layer_order;
protected:
    renderer(entity &attached_to);
    bool use_material_color(SDL_Renderer *renderer);
private:
    std::optional<::material> _material;
};

#endif
