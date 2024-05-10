#ifndef SNAKE_GAME_TILEMAZE_TILEMAZE_H
#define SNAKE_GAME_TILEMAZE_TILEMAZE_H

#include <engine/component/component.h>
#include <engine/vector2.h>

class tile_maze : public component
{
public:
    tile_maze(entity &attached_to, const vector2 &center, float tile_size);
    ~tile_maze() = default;
    vector2 center() const;
    float tile_size() const;
    vector2 tile_center(const vector2 &position) const;
private:
    const vector2 _center;
    const float _tile_size;
};

#endif
