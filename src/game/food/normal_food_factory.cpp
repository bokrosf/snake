#include <game/color.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>
#include <game/food/normal_food_factory.h>
#include <game/render_layer.h>

entity &normal_food_factory::create(unsigned int nutritional_value)
{
    entity &food = entity::create();
    food.add_component<::food>(nutritional_value);
    renderer &renderer = food.add_component<food_renderer>(render_layer::food);
    renderer.change_material(material{color::brave_strawberry});

    return food;
}