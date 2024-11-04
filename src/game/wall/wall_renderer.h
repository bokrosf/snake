#ifndef SNAKE_GAME_WALL_WALLRENDERER_H
#define SNAKE_GAME_WALL_WALLRENDERER_H

#include <engine/rendering/renderer.h>

class wall_renderer : public renderer
{
public:
    void render(SDL_Renderer *renderer) override;
};

#endif
