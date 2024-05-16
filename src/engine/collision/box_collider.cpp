#include <engine/collision/box_collider.h>

box_collider::box_collider(entity &attached_to)
    : box_collider(attached_to, vector2::zero())
{
}

box_collider::box_collider(entity &attached_to, const vector2 &area)
    : behavior(attached_to)
    , _area(area)
{
}

const vector2 &box_collider::area() const
{
    return _area;
}

void box_collider::area(const vector2 area)
{
    _area = area;
}
