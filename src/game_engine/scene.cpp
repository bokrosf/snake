#include "scene.h"

scene::~scene()
{
    for (auto root : _root_objects)
    {
        delete root;
    }
}

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

void scene::mark_as_destroyed(game_object &object)
{
    _objects_to_destroy.insert(&object);
}

void scene::destroy_marked_objects()
{
    for (auto destroyed : _objects_to_destroy)
    {
        destroyed->attach_to(nullptr);
    }

    for (auto destroyed : _objects_to_destroy)
    {
        _root_objects.erase(destroyed);
    }

    for (auto destroyed : _objects_to_destroy)
    {
        delete destroyed;
    }

    _objects_to_destroy.clear();
}
