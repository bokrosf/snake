#ifndef SNAKE_GAME_SNAKE_SNAKERENDERER_H
#define SNAKE_GAME_SNAKE_SNAKERENDERER_H

#include <engine/component/initializable.h>
#include <engine/rendering/renderer.h>
#include <game/snake/snake.h>
#include <game/tile_maze/tile_maze.h>

class snake_renderer : public renderer, public initializable
{
public:
    snake_renderer();
    void initialize() override;
    void render(SDL_Renderer *renderer) override;
private:
    int thickness() const;

    const snake *_snake;
    const tile_maze *_maze;
};

#endif
