#ifndef SNAKE_GAME_UI_BORDERRENDERER_H
#define SNAKE_GAME_UI_BORDERRENDERER_H

#include <engine/component/initializable.h>
#include <engine/entity.h>
#include <engine/rendering/renderer.h>
#include <game/ui/border.h>

class border_renderer : public renderer, public initializable
{
public:
    border_renderer(entity &attached_to);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    const border *_border;
};

#endif