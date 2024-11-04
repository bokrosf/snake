#ifndef SNAKE_GAME_FOOD_FOODRENDERER_H
#define SNAKE_GAME_FOOD_FOODRENDERER_H

#include <engine/component/initializable.h>
#include <engine/rendering/renderer.h>
#include <game/food/food.h>

class food_renderer : public renderer
{
public:
    void render(SDL_Renderer *renderer) override;
};

#endif
