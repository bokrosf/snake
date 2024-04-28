#ifndef SNAKE_GAME_WALL_WALLRENDERER_H
#define SNAKE_GAME_WALL_WALLRENDERER_H

#include <game_engine/component/renderer.h>
#include <game_engine/entity.h>
#include "wall.h"

class wall_renderer : public renderer
{
public:
    wall_renderer(entity &attached_to, int layer_order);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    wall *_wall;
};

#endif
