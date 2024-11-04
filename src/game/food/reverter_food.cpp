#include <game/food/reverter_food.h>

reverter_food::reverter_food(unsigned int nutritional_value)
    : food(nutritional_value)
{
}

void reverter_food::eat(snake &snake)
{
    snake.reverse();
}