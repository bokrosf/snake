#ifndef SNAKE_GAMEENGINE_COLLISION_BOXCOLLIDERRENDERER_H
#define SNAKE_GAMEENGINE_COLLISION_BOXCOLLIDERRENDERER_H

#include <game_engine/component/renderer.h>
#include <game_engine/game_object.h>
#include "box_collider.h"

class box_collider_renderer : public renderer
{
public:
    box_collider_renderer(game_object &attached_to, int render_order);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    box_collider *_collider;
};

#endif
