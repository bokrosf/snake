#ifndef SNAKE_GAME_FOOD_REVERTERFOOD_H
#define SNAKE_GAME_FOOD_REVERTERFOOD_H

#include <game/food/food.h>

class reverter_food : public food
{
public:
    reverter_food(unsigned int nutritional_value);
protected:
    void eat(snake &snake) override;
};

#endif