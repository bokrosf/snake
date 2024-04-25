#include "component.h"

component::component(game_object &attached_to)
    : _attached_to(attached_to)
{
}

component::~component()
{
}

void component::initialize()
{
}

void component::detach()
{
}

void component::destroy()
{
    attached_to().erase_component(*this);
}

game_object &component::attached_to() const
{
    return _attached_to;
}
