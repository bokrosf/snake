#ifndef SNAKE_FOOD_FOODFACTORY_H
#define SNAKE_FOOD_FOODFACTORY_H

#include <engine/entity.h>

class food_factory
{
public:
    virtual entity &create(unsigned int nutritional_value) = 0;
};

#endif