#include <utility>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/entity.h>
#include <engine/entity_name_collision.h>
#include <engine/life_state.h>
#include <engine/scene.h>
#include <engine/scene_traversal.h>

scene::scene(int id)
    : _id(id)
{
}

scene::~scene()
{
    for (auto root : _root_entities)
    {
        delete root;
    }
}

int scene::id() const
{
    return _id;
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

void scene::add(entity &entity)
{
    if (!entity.name().empty() && !_named_entities.insert(std::make_pair(entity.name(), &entity)).second)
    {
        throw entity_name_collision(std::string("Already exists an entity with name: ").append(entity.name()));
    }
    
    _initializer.add(entity);
    update_root_status(entity);
    entity._scene = this;
}

void scene::add(component &component)
{
    _initializer.add(component);
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

entity *scene::find_entity(const std::string &name) const
{
    auto it = _named_entities.find(name);

    return it != _named_entities.end() ? it->second : nullptr;
}

entity *scene::find_tagged_entity(const std::string &tag) const
{
    entity *found = nullptr;

    scene_traversal::traverse(
        *this,
        [&tag](const entity *e) { return e->tag() == tag; },
        [&found](entity *e) { found = e; });

    return found;
}

std::vector<entity *> scene::find_all_tagged_entity(const std::string &tag) const
{
    std::vector<entity *> found;

    scene_traversal::traverse(
        *this,
        [&tag](const entity *e) { return e->tag() == tag; },
        [&found](entity *e) { found.push_back(e); });

    return found;
}

std::generator<entity *> scene::root_entities() const
{
    for (auto e : _root_entities)
    {
        co_yield e;
    }
}

void scene::reset()
{
    for (auto e : _root_entities)
    {
        delete e;
    }

    _root_entities.clear();
    _entities_with_destroyed_component.clear();
    _entities_to_destroy.clear();
    _initializer = object_initializer();
    _named_entities.clear();

    initialize();
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
        
        if (!destroyed->name().empty())
        {
            _named_entities.erase(destroyed->name());
        }
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
