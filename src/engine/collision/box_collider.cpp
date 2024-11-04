#include <engine/collision/box_collider.h>

box_collider::box_collider()
    : box_collider(vector2::zero())
{
}

box_collider::box_collider(const vector2 &area)
    : _area(area)
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
