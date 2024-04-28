#ifndef SNAKE_GAME_SNAKE_SNAKERENDERER_H
#define SNAKE_GAME_SNAKE_SNAKERENDERER_H

#include <engine/rendering/renderer.h>
#include <game/snake/snake.h>

class snake_renderer : public renderer
{
public:
    snake_renderer(entity &attached_to, int layer_order, float thickness);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    void draw_segment(SDL_Renderer *renderer, const vector2 &start, const vector2 &end) const;
    int half_thickness() const;

    const snake *_snake;
    const float _thickness;
};

#endif
