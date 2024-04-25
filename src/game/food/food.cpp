#include <stdexcept>
#include <game/snake/snake.h>
#include "food.h"

food::food(game_object &attached_to, const vector2 &position, float nutritional_value)
    : behavior(attached_to)
    , _position(position)
    , _nutritional_value(0)
{
    if (nutritional_value < 0)
    {
        throw std::invalid_argument("Nutritional value must be greater than zero.");
    }

    _nutritional_value = nutritional_value;
}

const vector2 &food::position() const
{
    return _position;
}

void food::collide(const collision &collision)
{
    if (snake *snake = collision.collider.attached_to().find_component<::snake>())
    {
        eat(*snake);
        attached_to().destroy();
    }
}

void food::eat(snake &snake)
{
    snake.grow(_nutritional_value);
}
