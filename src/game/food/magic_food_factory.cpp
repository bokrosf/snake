#include <game/ability/inverted_snake_controller.h>
#include <game/ability/slow_down.h>
#include <game/ability/speed_boost.h>
#include <game/ability/wall_bouncing.h>
#include <game/color.h>
#include <game/food/food.h>
#include <game/food/food_renderer.h>
#include <game/food/magic_food.h>
#include <game/food/magic_food_factory.h>
#include <game/food/reverter_food.h>
#include <game/render_layer.h>

magic_food_factory::magic_food_factory()
    : _magic_food_ratio(5)
    , _normal_food_ratio(2 * _magic_food_ratio)
    , _distribution(1, _normal_food_ratio + _magic_food_ratio)
{
}

entity &magic_food_factory::create(unsigned int nutritional_value)
{
    entity &food = entity::create();
    renderer &renderer = food.add_component<food_renderer>(render_layer::food);

    int chance = _distribution(_generator);

    if (chance <= _normal_food_ratio)
    {
        food.add_component<::food>(nutritional_value);
        renderer.material(material{color::brave_strawberry});

        return food;
    }

    chance -= _normal_food_ratio;

    switch (chance)
    {
        case 1:
            food.add_component<magic_food<wall_bouncing>>(nutritional_value, 15.0F);
            renderer.material(material{color::fantastic_durian});
            break;
        case 2:
            food.add_component<magic_food<slow_down>>(nutritional_value, 5.0F);
            renderer.material(material{color::furious_orange});
            break;
        case 3:
            food.add_component<magic_food<speed_boost>>(nutritional_value, 10.0F);
            renderer.material(material{color::energetic_mango});
            break;
        case 4:
            food.add_component<magic_food<inverted_snake_controller>>(nutritional_value, 5.0F);
            renderer.material(material{color::sassy_grape});
            break;
        case 5:
            food.add_component<reverter_food>(nutritional_value);
            renderer.material(material{color::elegant_kiwi});
            break;
    }

    return food;
}