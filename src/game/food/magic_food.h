#ifndef SNAKE_GAME_FOOD_MAGICFOOD_H
#define SNAKE_GAME_FOOD_MAGICFOOD_H

#include <concepts>
#include <SDL2/SDL.h>
#include <game/ability/ability.h>
#include <game/ability/ability_slot.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>

template<typename Ability>
    requires std::derived_from<Ability, ability>
class magic_food : public food
{
public:
    magic_food(entity &attached_to, unsigned int nutritional_value);
protected:
    void eat(snake &snake) override;
};

template<typename Ability>
    requires std::derived_from<Ability, ability>
magic_food<Ability>::magic_food(entity &attached_to, unsigned int nutritional_value)
    : food(attached_to, nutritional_value)
{
}

template<typename Ability>
    requires std::derived_from<Ability, ability>
void magic_food<Ability>::eat(snake &snake)
{
    snake.grow(_nutritional_value);

    if (ability_slot *slot = attached_to().find_component<slot>())
    {
        food_renderer &renderer = attached_to().attached_component<food_renderer>();
        slot->add<Ability>(renderer.material()->color);
    }
}

#endif
