#include "food.h"

food::food(game_object &attached_to, const vector2 &position)
    : behavior(attached_to)
    , _position(position)
{
}

const vector2 &food::position() const
{
    return _position;
}
