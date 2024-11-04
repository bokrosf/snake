#ifndef SNAKE_GAME_ABILITY_ABILITYINDICATORRENDERER_H
#define SNAKE_GAME_ABILITY_ABILITYINDICATORRENDERER_H

#include <engine/component/initializable.h>
#include <engine/rendering/renderer.h>
#include <game/ability/ability_indicator.h>

class ability_indicator_renderer : public renderer, public initializable
{
public:
    ability_indicator_renderer();
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    ability_indicator *_indicator;
};

#endif