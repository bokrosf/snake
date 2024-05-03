#ifndef SNAKE_GAME_TILEMAZE_TILEMAZERENDERER_H
#define SNAKE_GAME_TILEMAZE_TILEMAZERENDERER_H

#include <engine/component/initializable.h>
#include <engine/entity.h>
#include <engine/rendering/renderer.h>
#include <engine/vector2.h>
#include <game/tile_maze/tile_maze.h>

class tile_maze_renderer : public renderer, public initializable
{
public:
    tile_maze_renderer(entity &attached_to, int layer_order, const vector2 &bounds);
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    const vector2 _bounds;
    const tile_maze *_maze;
};

#endif
