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

game_object &component::attached_to() const
{
    return _attached_to;
}
