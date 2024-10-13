#include <game/food/food.h>
#include <game/food/normal_food_factory.h>

entity &normal_food_factory::create(unsigned int nutritional_value)
{
    entity &food = entity::create();
    food.add_component<::food>(nutritional_value);

    return food;
}