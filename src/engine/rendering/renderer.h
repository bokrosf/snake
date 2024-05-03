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
    int layer_order() const;
    void change_material(const ::material &material);
protected:
    renderer(entity &attached_to, int layer_order);
    bool use_material_color(SDL_Renderer *renderer);
    
    std::optional<::material> _material;
private:
    const int _layer_order;
};

#endif
