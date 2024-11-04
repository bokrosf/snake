#ifndef SNAKE_GAME_TILEMAZE_TILEMAZE_H
#define SNAKE_GAME_TILEMAZE_TILEMAZE_H

#include <engine/component/component.h>
#include <engine/vector2.h>

struct tile_area
{
    ivector2 upper_left;
    ivector2 lower_right;
};

class tile_maze : public component
{
public:
    tile_maze(float tile_size, unsigned int width, unsigned int height);
    float tile_size() const;
    unsigned int width() const;
    unsigned int height() const;
    unsigned int tile_count() const;
    vector2 tile_center(unsigned int row, unsigned int column) const;
    tile_area tiles_of_area(const vector2 &upper_left, const vector2 &lower_right) const;
private:
    vector2 upper_left() const;
    ivector2 world_to_tile(const vector2 &world_position) const;

    const float _tile_size;
    const unsigned int _width;
    const unsigned int _height;
};

#endif
