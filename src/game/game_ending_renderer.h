#ifndef SNAKE_GAME_GAMEENDINGRENDERER_H
#define SNAKE_GAME_GAMEENDINGRENDERER_H

#include <engine/entity.h>
#include <engine/rendering/renderer.h>

class game_ending_renderer : public renderer
{
public:
    game_ending_renderer(entity &attached_to, int layer_order);
    ~game_ending_renderer() override = default;
    void render(SDL_Renderer *renderer) override;
};

#endif
