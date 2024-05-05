#include <stdexcept>
#include <game/food/food.h>
#include <game/game_event.h>
#include <game/snake/snake.h>

food::food(entity &attached_to, const vector2 &position, float nutritional_value)
    : behavior(attached_to)
    , _position(position)
    , _nutritional_value(0)
{
    if (nutritional_value < 0)
    {
        throw std::invalid_argument("Nutritional value must be greater than or equal to zero.");
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
    feed_snake(snake);
}

void food::feed_snake(snake &snake)
{
    snake.grow(_nutritional_value);
    _messenger.send(game_event::food_eaten);
}
