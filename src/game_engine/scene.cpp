#include "scene.h"

scene::scene(messenger &messenger)
    : _messenger(messenger)
{
}

scene::~scene()
{
    _messenger.unsubscribe<game_object_parent_changed>(*this);
}

void scene::initialize()
{
    _messenger.subscribe<game_object_parent_changed>(*this);
}

void scene::receive(const game_object_parent_changed &message)
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

void scene::receive(const component_added &message)
{
    _components_to_initialize.push(&message.added);
}
