#ifndef SNAKE_GAME_SNAKE_SNAKERENDERER_H
#define SNAKE_GAME_SNAKE_SNAKERENDERER_H

#include <game_engine/component/renderer.h>
#include "snake.h"

class snake_renderer : public renderer
{
public:
    snake_renderer(game_object &attached_to, int layer_order, float thickness);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    const snake *_snake;
    const float _thickness;
    void draw_segment(SDL_Renderer *renderer, const vector2 &start, const vector2 &end) const;
};

#endif
