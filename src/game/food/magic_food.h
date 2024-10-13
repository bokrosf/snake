#ifndef SNAKE_GAME_FOOD_MAGICFOOD_H
#define SNAKE_GAME_FOOD_MAGICFOOD_H

#include <concepts>
#include <game/food/food.h>
#include <game/ability/ability_slot.h>

template<typename Ability>
    requires std::derived_from<Ability, component>
class magic_food : public food
{
public:
    magic_food(entity &attached_to, const vector2 &position, float nutritional_value);
protected:
    void eat(snake &snake) override;
};

template<typename Ability>
    requires std::derived_from<Ability, component>
magic_food<Ability>::magic_food(entity &attached_to, const vector2 &position, float nutritional_value)
    : food(attached_to, position, nutritional_value)
{
}

template<typename Ability>
    requires std::derived_from<Ability, component>
void magic_food<Ability>::eat(snake &snake)
{
    snake.grow(_nutritional_value);

    if (ability_slot *slot = attached_to().find_component<slot>())
    {
        slot->add<Ability>();
    }
}

#endif
