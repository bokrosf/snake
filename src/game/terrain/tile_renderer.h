#ifndef SNAKE_GAME_TERRAIN_TILERENDERER_H
#define SNAKE_GAME_TERRAIN_TILERENDERER_H

#include <engine/component/renderer.h>

class tile_renderer : public renderer
{
public:
    tile_renderer(entity &attached_to, int layer_order, float tile_size);
    void render(SDL_Renderer *renderer) override;
private:
    float _tile_size;
};

#endif
