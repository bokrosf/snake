#include <game_engine/activatable.h>

activatable::activatable()
    : _active(true)
{
}

bool activatable::active() const
{
    return _active;
}

void activatable::activate(bool active)
{
    _active = active;
}
