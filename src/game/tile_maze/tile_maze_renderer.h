#ifndef SNAKE_GAME_TILEMAZE_TILEMAZERENDERER_H
#define SNAKE_GAME_TILEMAZE_TILEMAZERENDERER_H

#include <engine/rendering/renderer.h>
#include <engine/vector2.h>

struct tile_maze_renderer_configuration
{
    const float tile_size;
    const vector2 center;
    const vector2 bounds;
};

class tile_maze_renderer : public renderer
{
public:
    tile_maze_renderer(entity &attached_to, int layer_order, const tile_maze_renderer_configuration &configuration);
    void render(SDL_Renderer *renderer) override;
private:
    const tile_maze_renderer_configuration _configuration;
};

#endif
