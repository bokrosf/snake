#include <engine/entity.h>
#include <game/entity_name.h>
#include <game/fatal_collision_handler.h>
#include <game/game_event.h>

void fatal_collision_handler::collide(const collision &collision)
{
    if (collision.collider.attached_to().name() == entity_name::snake)
    {
        _messenger.send(game_event::game_lost);
    }
}
