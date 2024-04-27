#include "game_object.h"
#include "game_object_created.h"
#include "game_object_destroyed.h"
#include "game_object_parent_changed.h"
#include "component_destroyed.h"

game_object::game_object()
    : _life_state(life_state::alive)
    , _messenger(messenger::instance())
    , _parent(nullptr)
{
}

game_object::~game_object()
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

game_object &game_object::create()
{
    game_object *object = nullptr;

    try
    {
        object = new game_object();
    }
    catch (...)
    {
        delete object;
        throw;
    }

    messenger::instance().send(game_object_created(*object));

    return *object;
}

void game_object::destroy()
{
    if (_life_state == life_state::destroyed)
    {
        return;
    }
    
    _life_state = life_state::destroyed;
    _messenger.send(game_object_destroyed(*this));
}

life_state game_object::life_state() const
{
    return _life_state;
}

game_object *game_object::parent() const
{
    return _parent;
}

void game_object::attach_to(game_object *new_parent)
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
        _children.erase(std::find(_children.begin(), _children.end(), this));
    }

    game_object *descendant_tree_root = find_descendant_tree_root(new_parent);

    if (descendant_tree_root)
    {
        change_parent(descendant_tree_root, _parent);
    }

    change_parent(this, new_parent);
    _messenger.send(game_object_parent_changed(*this));

    if (descendant_tree_root)
    {
        _messenger.send(game_object_parent_changed(*descendant_tree_root));
    }
}

game_object *game_object::find_descendant_tree_root(game_object *descendant) const
{
    while (descendant && descendant->parent() != this)
    {
        descendant = descendant->parent();
    }

    return descendant;
}

void game_object::change_parent(game_object *object, game_object *new_parent)
{
    object->_parent = new_parent;

    if (new_parent)
    {
        new_parent->_children.push_back(object);
    }
}

void game_object::erase_destroyed_components()
{
    auto removed_begin = std::remove_if(_components.begin(), _components.end(), [](component *c) { return c->life_state() == life_state::destroyed; });
    std::for_each(removed_begin, _components.end(), [](component *c) { delete c; });
    _components.erase(removed_begin, _components.end());
}
