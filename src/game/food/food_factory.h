#ifndef SNAKE_FOOD_FOODFACTORY_H
#define SNAKE_FOOD_FOODFACTORY_H

#include <engine/entity.h>
#include <game/food/food.h>

class food_factory
{
public:
    virtual food &create(unsigned int nutritional_value) = 0;
};

#endif