#include <game/wall/wall.h>

wall::wall(entity &attached_to, const vector2 &area)
    : behavior(attached_to)
    , _area(area)
{
}

const vector2 &wall::area() const
{
    return _area;
}