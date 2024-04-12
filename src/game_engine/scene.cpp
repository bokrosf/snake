#include "scene.h"

void scene::update_root_status(game_object &object)
{
    if (object.parent())
    {
        _root_objects.erase(&object);
    }
    else
    {
        _root_objects.insert(&object);
    }
}

void scene::register_added_component(component &added)
{
    _components_to_initialize.push(&added);
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
