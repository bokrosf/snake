#include <engine/entity.h>
#include <game/ui/border.h>

border::border()
    : _thickness(0)
{
}

const vector2 &border::inner_area() const
{
    return _inner_area;
}

void border::inner_area(const vector2 &value)
{
    _inner_area = value;
}

float border::thickness() const
{
    return _thickness;
}

void border::thickness(float value)
{
    _thickness = value;
}
