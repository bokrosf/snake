#include <stdexcept>
#include <game/food/food.h>
#include <game/game_event.h>
#include <game/snake/snake.h>

food::food(entity &attached_to, unsigned int nutritional_value)
    : behavior(attached_to)
    , _nutritional_value(nutritional_value)
{
    if (nutritional_value < 0)
    {
        throw std::invalid_argument("Nutritional value must be greater than or equal to zero.");
    }
}

void food::collide(const collision &collision)
{
    if (snake *snake = collision.collider.attached_to().find_component<::snake>())
    {
        snake->grow(_nutritional_value);
        eat(*snake);
        _messenger.send(game_event::food_eaten);
        attached_to().destroy();
    }
}

void food::eat(snake &snake)
{
}