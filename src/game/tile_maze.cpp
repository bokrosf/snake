#include <stdexcept>
#include <game/tile_maze.h>

tile_maze::tile_maze(entity &attached_to, const vector2 &center, float tile_size)
    : component(attached_to)
    , _center(center)
    , _tile_size(tile_size)
{
    if (tile_size <= 0)
    {
        throw std::invalid_argument("Tile size must be greater than zero.");
    }
}

vector2 tile_maze::center() const
{
    return _center;
}

vector2 tile_maze::tile_center(const vector2 &position) const
{
    vector2 difference = _center.points_to(position);
    vector2 difference_in_tiles = (difference / _tile_size).truncate();

    return _center + _tile_size * difference_in_tiles;
}
