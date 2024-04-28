#include <game/wall/wall.h>

wall::wall(entity &attached_to, const vector2 &position, const vector2 &area)
    : behavior(attached_to)
    , _position(position)
    , _area(area)
{
}

const vector2 &wall::position() const
{
    return _position;
}

const vector2 &wall::area() const
{
    return _area;
}
