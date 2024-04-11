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
    _uninitialized_components.push(&message.added);
}
