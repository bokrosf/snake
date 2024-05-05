#include <queue>
#include <ranges>
#include <engine/scene_traversal.h>

void scene_traversal::traverse(const scene &scene, std::function<bool(const entity *)> filter, std::function<void(entity *)> operation)
{
    std::queue<entity *> checked_entities;

    for (entity *entity : scene.root_entities() | std::views::filter(filter))
    {
        checked_entities.push(entity);
    }

    while (!checked_entities.empty())
    {
        entity *entity = checked_entities.front();
        checked_entities.pop();
        operation(entity);

        for (::entity *child : entity->children() | std::views::filter(filter))
        {
            checked_entities.push(child);
        }
    }
}
