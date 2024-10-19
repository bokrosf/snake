#ifndef SNAKE_GAME_FOOD_MAGICFOODFACTORY_H
#define SNAKE_GAME_FOOD_MAGICFOODFACTORY_H

#include <random>
#include <game/food/food_factory.h>

class magic_food_factory : public food_factory
{
public:
    magic_food_factory();
    entity &create(unsigned int nutritional_value) override;
private:
    const int _magic_food_ratio;
    const int _normal_food_ratio;
    std::random_device _generator;
    std::uniform_int_distribution<int> _distribution;
};

#endif