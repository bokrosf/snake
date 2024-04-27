#include <game_engine/game_object.h>
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

void scene::mark_as_destroyed(component &component)
{
    _objects_with_destroyed_component.insert(&component.attached_to());
}

void scene::destroy_marked_objects()
{
    destroy_components();
    destroy_game_objects();
}

void scene::destroy_components()
{
    for (game_object *object : _objects_with_destroyed_component)
    {
        if (!_objects_to_destroy.contains(object))
        {
            object->erase_destroyed_components();
        }
    }
    
    _objects_with_destroyed_component.clear();
}

void scene::destroy_game_objects()
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
