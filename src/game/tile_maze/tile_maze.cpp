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
    vector2 difference = transformation().position().points_to(position);
    vector2 difference_in_tiles = (difference / _tile_size).round();

    return transformation().position() + _tile_size * difference_in_tiles;
}
