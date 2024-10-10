#include <engine/input.h>
#include <engine/vector2.h>
#include <game/snake/snake_controller.h>

snake_controller::snake_controller(entity &attached_to)
    : behavior(attached_to)
    , _snake(nullptr)
{
}

void snake_controller::initialize()
{
    _snake = &attached_to().attached_component<snake>();
}

void snake_controller::update()
{
    if (input::key_down(SDLK_w) || input::key_down(SDLK_UP))
    {
        _snake->look_in_direction(ivector2::down());
    }
    else if (input::key_down(SDLK_s) || input::key_down(SDLK_DOWN))
    {
        _snake->look_in_direction(ivector2::up());
    }
    else if (input::key_down(SDLK_a) || input::key_down(SDLK_LEFT))
    {
        _snake->look_in_direction(ivector2::left());
    }
    else if (input::key_down(SDLK_d) || input::key_down(SDLK_RIGHT))
    {
        _snake->look_in_direction(ivector2::right());
    }
}
