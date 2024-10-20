#include <engine/component/transform.h>

transform::transform(entity &attached_to)
    : component(attached_to)
{
}

const vector2 &transform::position() const
{
    return _position;
}

void transform::position(const vector2 &position)
{
    _position = position;
}

void transform::translate(const vector2 &translation)
{
    _position += translation;
}

const vector2 &transform::scale() const
{
    return _scale;
}

void transform::scale(const vector2 &scaling)
{
    _scale = scaling;
}
