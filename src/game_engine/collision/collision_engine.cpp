#include <algorithm>
#include <cmath>
#include <ranges>
#include <game_engine/activatable.h>
#include <game_engine/collision/collision.h>
#include <game_engine/collision/collision_engine.h>
#include <game_engine/scene_traversal.h>

void collision_engine::detect_collisions(const scene &scene)
{
    std::vector<box_collider *> colliders = collect_colliders(scene);

    for (box_collider *current : colliders)
    {
        std::unordered_set<entity *> collided_entities;
        
        for (box_collider *other : colliders | std::views::filter([current](box_collider *c) { return c != current; }))
        {
            vector2 difference = current->center().points_to(other->center());
            float x_threshold = std::abs(current->area().x()) + std::abs(other->area().x());
            float y_threshold = std::abs(current->area().y()) + std::abs(other->area().y());
            
            if (std::abs(difference.x()) < x_threshold && std::abs(difference.y()) < y_threshold)
            {
                collided_entities.insert(&other->attached_to());
            }
        }

        notify_collided_entities(*current, collided_entities);
    }
}

std::vector<box_collider *> collision_engine::collect_colliders(const scene &scene) const
{
    std::vector<box_collider *> colliders;

    auto add_collider = [&colliders](entity *entity)
    {
        auto collider_filter = [](box_collider *c) { return c->active(); };

        for (box_collider *c : entity->all_attached_components<box_collider>() | std::views::filter(collider_filter))
        {
            colliders.push_back(c);
        }
    };

    scene_traversal::traverse(scene, scene_traversal::filter_active_entity, add_collider);

    return colliders;
}

void collision_engine::notify_collided_entities(box_collider &collider, const std::unordered_set<entity *> &collided_entities) const
{
    collision collision{collider};

    for (entity *collided_with : collided_entities)
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
