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

const vector2 &transformation::scale() const
{
    return _scale;
}

void transformation::scale(const vector2 &scaling)
{
    _scale = scaling;
}
