#include <game/color.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>
#include <game/food/magic_food_factory.h>
#include <game/render_layer.h>

entity &magic_food_factory::create(unsigned int nutritional_value)
{
    entity &food = entity::create();
    food.add_component<::food>(nutritional_value);
    food.add_component<food_renderer>(render_layer::food);
    food.attached_component<food_renderer>().change_material(material{color::brave_strawberry});

    return food;
}