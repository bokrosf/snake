#include <game/food/normal_food_factory.h>

food &normal_food_factory::create(unsigned int nutritional_value)
{
    entity &created = entity::create();
    
    return created.add_component<food>(nutritional_value);
}