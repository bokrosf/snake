#include <ranges>
#include <game/ability/wall_bouncing.h>
#include <game/tag.h>

wall_bouncing::wall_bouncing(entity &attached_to, float duration)
    : ability(attached_to, duration)
{
}

void wall_bouncing::start()
{
    ability::start();
    
    for (auto &entity : attached_to().find_all_tagged(tag::wall))
    {
        fatal_collision_handler *handler = &entity.attached_component<fatal_collision_handler>();
        handler->active(false);
        _deactivated_handlers.push_back(handler);
        _added_handlers.push_back(&entity.add_component<bouncing_collision_handler>());
    }
}

void wall_bouncing::detach()
{
    for (auto *handler : _deactivated_handlers)
    {
        handler->active(true);
    }

    for (auto *handler : _added_handlers)
    {
        handler->destroy();
    }
}