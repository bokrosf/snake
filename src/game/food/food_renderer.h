#ifndef SNAKE_GAME_FOOD_FOODRENDERER_H
#define SNAKE_GAME_FOOD_FOODRENDERER_H

#include <engine/rendering/renderer.h>
#include <game/food/food.h>

class food_renderer : public renderer
{
public:
    food_renderer(entity &attached_to, int layer_order, float thickness);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    float _thickness;
    const food *_food;
};

#endif
