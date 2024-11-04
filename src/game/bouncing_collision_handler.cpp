#include <engine/entity.h>
#include <game/bouncing_collision_handler.h>
#include <game/entity_name.h>
#include <game/snake/snake.h>

void bouncing_collision_handler::collide(const collision &collision)
{
    if (snake *snake = collision.collider.attached_to().find_component<::snake>())
    {
        snake->reverse();
        snake->move_forward(1);
    }
}
