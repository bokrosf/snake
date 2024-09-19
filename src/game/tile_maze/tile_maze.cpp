#include <stdexcept>
#include <game/tile_maze/tile_maze.h>

tile_maze::tile_maze(entity &attached_to, float tile_size)
    : component(attached_to)
    , _tile_size(tile_size)
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

vector2 tile_maze::tile_center(const vector2 &position) const
{
    return transformation().position() + _tile_size * difference_in_tiles(transformation().position(), position);
}

vector2 tile_maze::difference_in_tiles(const vector2 &a, const vector2 &b) const
{
    return (a.points_to(b) / _tile_size).round();
}
