#ifndef SNAKE_GAME_TERRAIN_TILERENDERER_H
#define SNAKE_GAME_TERRAIN_TILERENDERER_H

#include <engine/rendering/renderer.h>
#include <engine/vector2.h>

struct tile_renderer_configuration
{
    const float tile_size;
    const vector2 center;
    const vector2 bounds;
};

class tile_renderer : public renderer
{
public:
    tile_renderer(entity &attached_to, int layer_order, const tile_renderer_configuration &configuration);
    void render(SDL_Renderer *renderer) override;
private:
    const tile_renderer_configuration _configuration;
};

#endif
