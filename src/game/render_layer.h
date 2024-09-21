#ifndef SNAKE_GAME_RENDERLAYER_H
#define SNAKE_GAME_RENDERLAYER_H

namespace render_layer
{
    const int collider = 99;
    const int terrain = 0;
    const int wall = terrain + 1;
    const int food = terrain + 1;
    const int snake = food + 1;
}

#endif
