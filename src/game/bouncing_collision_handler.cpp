#include <game/bouncing_collision_handler.h>
#include <game/entity_name.h>
#include <game/snake/snake.h>

bouncing_collision_handler::bouncing_collision_handler(entity &attached_to)
    : behavior(attached_to)
{
}

void bouncing_collision_handler::collide(const collision &collision)
{
    if (snake *snake = collision.collider.attached_to().find_component<::snake>())
    {
        snake->reverse();
        snake->move_forward(1);
    }
}
