#ifndef SNAKE_ENGINE_COLLISION_BOXCOLLIDERRENDERER_H
#define SNAKE_ENGINE_COLLISION_BOXCOLLIDERRENDERER_H

#include <engine/collision/box_collider.h>
#include <engine/component/renderer.h>
#include <engine/entity.h>

class box_collider_renderer : public renderer
{
public:
    box_collider_renderer(entity &attached_to, int render_order);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    box_collider *_collider;
};

#endif
