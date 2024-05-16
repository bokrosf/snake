#include <engine/component/transformation.h>

transformation::transformation(entity &attached_to)
    : component(attached_to)
{
}

const vector2 &transformation::position() const
{
    return _position;
}

void transformation::position(const vector2 &position)
{
    _position = position;
}

void transformation::translate(const vector2 &translation)
{
    _position += translation;
}
