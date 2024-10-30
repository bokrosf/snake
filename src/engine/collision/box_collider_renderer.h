#ifndef ENGINE_COLLISION_BOXCOLLIDERRENDERER_H
#define ENGINE_COLLISION_BOXCOLLIDERRENDERER_H

#include <engine/collision/box_collider.h>
#include <engine/component/initializable.h>
#include <engine/entity.h>
#include <engine/rendering/renderer.h>

class box_collider_renderer : public renderer, public initializable
{
public:
    box_collider_renderer(entity &attached_to);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    const box_collider *_collider;
};

#endif
