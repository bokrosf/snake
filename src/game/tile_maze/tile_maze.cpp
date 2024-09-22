#include <stdexcept>
#include <game/tile_maze/tile_maze.h>

tile_maze::tile_maze(entity &attached_to, float tile_size, uint width, uint height)
    : component(attached_to)
    , _tile_size(tile_size)
    , _width(width)
    , _height(height)
{
    if (tile_size <= 0)
    {
        throw std::invalid_argument("Tile size must be greater than zero.");
    }
}

float tile_maze::tile_size() const
{
    return _tile_size;
}

uint tile_maze::width() const
{
    return _width;
}

uint tile_maze::height() const
{
    return _height;
}

uint tile_maze::tile_count() const
{
    return _width * _height;
}

vector2 tile_maze::tile_center(const vector2 &position) const
{
    return transformation().position() + _tile_size * difference_in_tiles(transformation().position(), position);
}

vector2 tile_maze::tile_center(uint row, uint column) const
{
    vector2 upper_left_corner = transformation().position() - _tile_size * vector2(_width / 2, _height / 2);
    
    return upper_left_corner + _tile_size * vector2(column, row);
}

std::generator<vector2> tile_maze::tiles_of_area(const vector2 &center, const vector2 &area) const
{
    vector2 tile_count = (area.absolute() / _tile_size).round();
    vector2 upper_left_corner = center - 0.5 * area.absolute();
    upper_left_corner += 0.5F * vector2(_tile_size, _tile_size);

    for (int row = 0; row < tile_count.y; ++row)
    {
        for (int column = 0; column < tile_count.x; ++column)
        {
            vector2 tile(column * _tile_size, row * _tile_size);
            co_yield tile_center(upper_left_corner + tile);
        }
    }
}

vector2 tile_maze::difference_in_tiles(const vector2 &a, const vector2 &b) const
{
    return (a.points_to(b) / _tile_size).round();
}
