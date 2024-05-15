#include <engine/entity.h>
#include <engine/entity_created.h>
#include <engine/entity_destroyed.h>
#include <engine/entity_parent_changed.h>
#include <engine/component_destroyed.h>

entity::entity()
    : _life_state(life_state::initializing)
    , _messenger(messenger::instance())
    , _parent(nullptr)
{
}

entity::~entity()
{
    for (auto c : _components)
    {
        delete c;
    }

    for (auto c : _children)
    {
        delete c;
    }
}

entity &entity::create()
{
    entity *entity = nullptr;

    try
    {
        entity = new ::entity();
    }
    catch (...)
    {
        delete entity;
        throw;
    }

    messenger::instance().send(entity_created{*entity});
    entity->_transformation = &entity->add_component<::transformation>();

    return *entity;
}

void entity::destroy()
{
    if (_life_state == life_state::destroyed)
    {
        return;
    }
    
    _life_state = life_state::destroyed;
    _messenger.send(entity_destroyed{*this});
}

life_state entity::life_state() const
{
    return _life_state;
}

entity *entity::parent() const
{
    return _parent;
}

transformation &entity::transformation()
{
    return *_transformation;
}

void entity::attach_to(entity *new_parent)
{
    if (new_parent == this)
    {
        throw std::invalid_argument("Current instance can not be it's own parent.");
    }

    if (new_parent == _parent)
    {
        return;
    }

    if (_parent)
    {
        std::erase(_children, this);
    }

    entity *descendant_tree_root = find_descendant_tree_root(new_parent);

    if (descendant_tree_root)
    {
        change_parent(descendant_tree_root, _parent);
    }

    change_parent(this, new_parent);
    _messenger.send(entity_parent_changed{*this});

    if (descendant_tree_root)
    {
        _messenger.send(entity_parent_changed{*descendant_tree_root});
    }
}

entity *entity::find_descendant_tree_root(entity *descendant) const
{
    while (descendant && descendant->parent() != this)
    {
        descendant = descendant->parent();
    }

    return descendant;
}

void entity::change_parent(entity *entity, ::entity *new_parent)
{
    entity->_parent = new_parent;

    if (new_parent)
    {
        new_parent->_children.push_back(entity);
    }
}

void entity::erase_destroyed_components()
{
    auto removed_begin = std::remove_if(_components.begin(), _components.end(), [](component *c) { return c->life_state() == life_state::destroyed; });
    std::for_each(removed_begin, _components.end(), [](component *c) { delete c; });
    _components.erase(removed_begin, _components.end());
}
