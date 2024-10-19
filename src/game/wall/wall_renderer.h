#ifndef SNAKE_GAME_WALL_WALLRENDERER_H
#define SNAKE_GAME_WALL_WALLRENDERER_H

#include <engine/entity.h>
#include <engine/rendering/renderer.h>

class wall_renderer : public renderer
{
public:
    wall_renderer(entity &attached_to, int layer_order);
    void render(SDL_Renderer *renderer) override;
};

#endif
