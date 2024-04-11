#include "scene.h"

void scene::update_root_objects(const game_object_parent_changed &message)
{
    if (message.object.parent())
    {
        _root_objects.erase(&message.object);
    }
    else
    {
        _root_objects.insert(&message.object);
    }
}

void scene::register_added_component(const component_added &message)
{
    _components_to_initialize.push(&message.added);
}

void scene::initialize_components()
{
    while (!_components_to_initialize.empty())
    {
        _components_to_initialize.front()->initialize();
        _components_to_initialize.pop();
    }
}

std::ranges::ref_view<const std::unordered_set<game_object *>> scene::root_objects() const
{
    return std::views::all(_root_objects);
}
