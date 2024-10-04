#ifndef SNAKE_GAME_TILEMAZE_TILEMAZE_H
#define SNAKE_GAME_TILEMAZE_TILEMAZE_H

#include <generator>
#include <engine/component/component.h>
#include <engine/entity.h>
#include <engine/vector2.h>

class tile_maze : public component
{
public:
    tile_maze(entity &attached_to, float tile_size, unsigned int width, unsigned int height);
    float tile_size() const;
    unsigned int width() const;
    unsigned int height() const;
    unsigned int tile_count() const;
    vector2 tile_center(const vector2 &position) const;
    vector2 tile_center(unsigned int row, unsigned int column) const;
    std::generator<vector2> tiles_of_area(const vector2 &center, const vector2 &area) const;
private:
    vector2 difference_in_tiles(const vector2 &a, const vector2 &b) const;

    const float _tile_size;
    const unsigned int _width;
    const unsigned int _height;
};

#endif
