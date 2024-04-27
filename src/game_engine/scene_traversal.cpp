#include <queue>
#include <ranges>
#include "scene_traversal.h"

bool scene_traversal::filter_active_object(const game_object *object)
{
    return object->active();
}

void scene_traversal::traverse(const scene &scene, std::function<bool(const game_object *)> filter, std::function<void(game_object *)> operation)
{
    std::queue<game_object *> checked_objects;

    for (game_object *object : scene.root_objects() | std::views::filter(filter))
    {
        checked_objects.push(object);
    }

    while (!checked_objects.empty())
    {
        game_object *object = checked_objects.front();
        checked_objects.pop();
        operation(object);

        for (game_object *child : object->children() | std::views::filter(filter))
        {
            checked_objects.push(child);
        }
    }
}
