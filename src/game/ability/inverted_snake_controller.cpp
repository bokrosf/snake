#include <engine/entity.h>
#include <engine/input.h>
#include <game/ability/inverted_snake_controller.h>
#include <game/execution_priority.h>
#include <game/snake/snake_controller.h>

inverted_snake_controller::inverted_snake_controller(float duration)
    : ability(duration)
    , _snake(nullptr)
    , _original_controller(nullptr)
{
    priority = execution_priority::controller;
}

void inverted_snake_controller::initialize()
{
    _snake = &attached_to().attached_component<snake>();
    _original_controller = &attached_to().attached_component<snake_controller>();
}

void inverted_snake_controller::start()
{
    ability::start();
    _original_controller->active(false);
}

void inverted_snake_controller::update_effect()
{
    if (input::key_down(SDLK_w) || input::key_down(SDLK_UP))
    {
        _snake->look_in_direction(ivector2::up());
    }
    else if (input::key_down(SDLK_s) || input::key_down(SDLK_DOWN))
    {
        _snake->look_in_direction(ivector2::down());
    }
    else if (input::key_down(SDLK_a) || input::key_down(SDLK_LEFT))
    {
        _snake->look_in_direction(ivector2::right());
    }
    else if (input::key_down(SDLK_d) || input::key_down(SDLK_RIGHT))
    {
        _snake->look_in_direction(ivector2::left());
    }
}

void inverted_snake_controller::detach()
{
    _original_controller->active(true);
}
