#include <stdexcept>
#include <game/tile_maze/tile_maze.h>

tile_maze::tile_maze(entity &attached_to, float tile_size, unsigned int width, unsigned int height)
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

unsigned int tile_maze::width() const
{
    return _width;
}

unsigned int tile_maze::height() const
{
    return _height;
}

unsigned int tile_maze::tile_count() const
{
    return _width * _height;
}

vector2 tile_maze::tile_center(unsigned int row, unsigned int column) const
{
    vector2 tile_position = vector2(column * _tile_size, row * _tile_size);
    vector2 center_offset = 0.5F * vector2(_tile_size, _tile_size);

    return upper_left() + tile_position + center_offset;
}

tile_area tile_maze::tiles_of_area(const vector2 &upper_left, const vector2 &lower_right) const
{
    vector2 maze_upper_left = this->upper_left();
    
    if (upper_left.x < maze_upper_left.x && upper_left.y < maze_upper_left.y)
    {
        throw std::invalid_argument("Upper left position must be inside the maze.");
    }

    vector2 maze_lower_right = maze_upper_left + _tile_size * vector2(_width, _height);

    if (lower_right.x > maze_lower_right.x && lower_right.y > maze_lower_right.y)
    {
        throw std::invalid_argument("Lower right position must be inside the maze.");
    }

    tile_area area;
    area.upper_left = world_to_tile(upper_left);
    area.lower_right = world_to_tile(lower_right);

    return area;
}

vector2 tile_maze::upper_left() const
{
    return transform().position() - 0.5F * _tile_size * vector2(_width, _height);
}

ivector2 tile_maze::world_to_tile(const vector2 &world_position) const
{
    vector2 difference = (upper_left().points_to(world_position) / _tile_size).trunc();

    return ivector2(
        static_cast<int>(difference.x),
        static_cast<int>(difference.y));
}
