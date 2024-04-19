#include "box_collider.h"

box_collider::box_collider(game_object &attached_to, const vector2 &center)
    : box_collider(attached_to, center, vector2::zero())
{
}

box_collider::box_collider(game_object &attached_to, const vector2 &center, const vector2 &area)
    : component(attached_to)
    , _center(center)
    , _area(area)
{
}

const vector2 &box_collider::center() const
{
    return _center;
}

void box_collider::reposition(const vector2 &center)
{
    _center = center;
}

const vector2 &box_collider::area() const
{
    return _area;
}
