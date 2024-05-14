#include <engine/component/transformation.h>

transformation::transformation(entity &attached_to)
    : component(attached_to)
{
}

void transformation::translate(const vector2 &translation)
{
    _position += translation;
}
