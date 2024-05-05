#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/entity.h>
#include <engine/life_state.h>
#include <engine/scene.h>

scene::~scene()
{
    for (auto root : _root_entities)
    {
        delete root;
    }
}

void scene::update_root_status(entity &entity)
{
    if (entity.parent())
    {
        _root_entities.erase(&entity);
    }
    else
    {
        _root_entities.insert(&entity);
    }
}

void scene::register_created_entity(entity &created)
{
    _initializer.add(created);
    update_root_status(created);
}

void scene::register_added_component(component &added)
{
    _initializer.add(added);
}

void scene::initialize_objects()
{
    _initializer.initialize_objects();
}

void scene::mark_as_destroyed(entity &entity)
{
    _entities_to_destroy.insert(&entity);
}

void scene::mark_as_destroyed(component &component)
{
    _entities_with_destroyed_component.insert(&component.attached_to());
}

void scene::destroy_marked_objects()
{
    destroy_components();
    destroy_entities();
}

void scene::destroy_components()
{
    for (entity *entity : _entities_with_destroyed_component)
    {
        if (!_entities_to_destroy.contains(entity))
        {
            entity->erase_destroyed_components();
        }
    }
    
    _entities_with_destroyed_component.clear();
}

void scene::destroy_entities()
{
    for (auto destroyed : _entities_to_destroy)
    {
        destroyed->attach_to(nullptr);
    }

    for (auto destroyed : _entities_to_destroy)
    {
        _root_entities.erase(destroyed);
    }

    for (auto destroyed : _entities_to_destroy)
    {
        delete destroyed;
    }

    _entities_to_destroy.clear();
}
