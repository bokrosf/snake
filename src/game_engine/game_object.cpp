#include "game_object.h"
#include "game_object_parent_changed.h"

game_object::game_object(messenger &messenger)
    : _parent(nullptr)
    , _messenger(messenger)
{
}

game_object::~game_object()
{
    for (auto c : _components)
    {
        delete c;
    }
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

    _parent = new_parent;
    
    if (_parent)
    {
        _parent->_children.push_back(this);
    }

    _messenger.send(game_object_parent_changed(*this));
}

std::ranges::ref_view<const std::vector<game_object *>> game_object::children() const
{
    return std::views::all(_children);
}

void game_object::erase_component(const component &erased)
{
    auto it = std::find(_components.begin(), _components.end(), &erased);

    if (it != _components.end())
    {
        delete *it;
        _components.erase(it);
    }
}
