#include <game/food/food.h>
#include <game/food/magic_food_factory.h>

entity &magic_food_factory::create(unsigned int nutritional_value)
{
    entity &created = entity::create();
    created.add_component<food>(nutritional_value);

    return created;
}