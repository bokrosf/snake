#include <game_engine/component_destroyed.h>
#include "component.h"

component::component(entity &attached_to)
    : _life_state(life_state::alive)
    , _attached_to(attached_to)
    , _messenger(messenger::instance())
{
}

void component::initialize()
{
}

void component::destroy()
{
    if (_life_state == life_state::destroyed)
    {
        return;
    }

    _life_state = life_state::destroyed;
    detach();
    _messenger.send(component_destroyed{*this});
}

life_state component::life_state() const
{
    return _life_state;
}

entity &component::attached_to() const
{
    return _attached_to;
}

void component::detach()
{
}
