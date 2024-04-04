#ifndef SNAKE_GAMEENGINE_COMPONENT_ADDED_H
#define SNAKE_GAMEENGINE_COMPONENT_ADDED_H

#include "component/component.h"

struct component_added
{
    component &added;

    component_added(component &added)
        : added(added)
    {
    }
};

#endif
