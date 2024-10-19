#ifndef SNAKE_GAME_FOOD_NORMALFOODFACTORY_H
#define SNAKE_GAME_FOOD_NORMALFOODFACTORY_H

#include <game/food/food_factory.h>

class normal_food_factory : public food_factory
{
public:
    entity &create(unsigned int nutritional_value) override;
};

#endif