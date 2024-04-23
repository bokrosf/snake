#include <cmath>
#include <algorithm>
#include <ranges>
#include <game_engine/activatable.h>
#include "collision.h"
#include "collision_engine.h"

void collision_engine::detect_collisions(const scene *scene)
{
    std::vector<box_collider *> colliders = collect_colliders(scene);

    for (box_collider *current : colliders)
    {
        std::unordered_set<game_object *> collided_objects;
        
        for (box_collider *other : colliders | std::views::filter([current](box_collider *c) { return c != current; }))
        {
            vector2 difference = current->center().points_to(other->center());
            
            float max_x = std::max(std::abs(other->area().x()), std::abs(current->area().x()));
            float max_y = std::max(std::abs(other->area().y()), std::abs(current->area().y()));

            if (std::abs(difference.x()) < max_x && std::abs(difference.y()) < max_y)
            {
                collided_objects.insert(&other->attached_to());
            }
        }

        collision collision{current->attached_to()};

        for (game_object *collided_with : collided_objects)
        {
            for (component *c : collided_with->all_attached_components<component>())
            {
                collision_handler *handler = dynamic_cast<collision_handler *>(c);
                activatable *activatable = dynamic_cast<::activatable *>(c);
                
                if (handler && (!activatable || activatable->active()))
                {
                    handler->collide(collision);
                }
            }
        }
    }
}

std::vector<box_collider *> collision_engine::collect_colliders(const scene *scene)
{
    std::queue<game_object *> checked_objects;
    std::vector<box_collider *> colliders;
    auto active_object_filter = [](const game_object *object) { return object->active(); };
    
    for (game_object *object : scene->root_objects() | std::views::filter(active_object_filter))
    {
        checked_objects.push(object);
    }

    while (!checked_objects.empty())
    {
        game_object *object = checked_objects.front();
        checked_objects.pop();
        auto collider_filter = [](box_collider *c) { return c->active(); };

        for (box_collider *c : object->all_attached_components<box_collider>() | std::views::filter(collider_filter))
        {
            colliders.push_back(c);
        }

        for (game_object *child : object->children() | std::views::filter(active_object_filter))
        {
            checked_objects.push(child);
        }
    }

    return colliders;
}
