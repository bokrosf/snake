#include <engine/input.h>
#include <game/ability/inverted_snake_controller.h>
#include <game/snake/snake_controller.h>

inverted_snake_controller::inverted_snake_controller(entity &attached_to, float duration)
    : ability(attached_to, duration)
{
}

void inverted_snake_controller::initialize()
{
    ability::initialize();
    _original_controller = &attached_to().attached_component<snake_controller>();
}

void inverted_snake_controller::start()
{
    ability::start();
    _original_controller->activate(false);
}

void inverted_snake_controller::update_effect()
{
    if (input::key_down(SDLK_w) || input::key_down(SDLK_UP))
    {
        snake().look_in_direction(ivector2::up());
    }
    else if (input::key_down(SDLK_s) || input::key_down(SDLK_DOWN))
    {
        snake().look_in_direction(ivector2::down());
    }
    else if (input::key_down(SDLK_a) || input::key_down(SDLK_LEFT))
    {
        snake().look_in_direction(ivector2::right());
    }
    else if (input::key_down(SDLK_d) || input::key_down(SDLK_RIGHT))
    {
        snake().look_in_direction(ivector2::left());
    }
}

void inverted_snake_controller::detach()
{
    _original_controller->activate(true);
}
