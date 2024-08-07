#ifndef SNAKE_GAME_WALL_WALLRENDERER_H
#define SNAKE_GAME_WALL_WALLRENDERER_H

#include <engine/component/initializable.h>
#include <engine/entity.h>
#include <engine/rendering/renderer.h>
#include <game/wall/wall.h>

class wall_renderer : public renderer, public initializable
{
public:
    wall_renderer(entity &attached_to, int layer_order);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    wall *_wall;
};

#endif
