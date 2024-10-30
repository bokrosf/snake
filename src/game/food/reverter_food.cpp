#include <game/food/reverter_food.h>

reverter_food::reverter_food(entity &attached_to, unsigned int nutritional_value)
    : food(attached_to, nutritional_value)
{
}

void reverter_food::eat(snake &snake)
{
    snake.reverse();
}