#ifndef SNAKE_GAMEENGINE_COMPONENTADDED_H
#define SNAKE_GAMEENGINE_COMPONENTADDED_H

class component;

struct component_added
{
    component &added;

    component_added(component &added)
        : added(added)
    {
    }
};

#endif
