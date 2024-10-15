#ifndef SNAKE_GAME_FOOD_MAGICFOODFACTORY_H
#define SNAKE_GAME_FOOD_MAGICFOODFACTORY_H

#include <random>
#include <game/food/food_factory.h>

class magic_food_factory : public food_factory
{
public:
    magic_food_factory() = default;
    entity &create(unsigned int nutritional_value) override;
private:
    std::random_device _generator;
    std::uniform_int_distribution<int> _distribution;
};

#endif