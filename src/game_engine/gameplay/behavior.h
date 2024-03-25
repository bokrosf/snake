#ifndef SNAKE_GAMEENGINE_GAMEPLAY_BEHAVIOR_H
#define SNAKE_GAMEENGINE_GAMEPLAY_BEHAVIOR_H

#include "component.h"
#include "updatable.h"
#include "activatable.h"

class behavior : public component, public updatable, public activatable
{
protected:
    behavior(game_object &attached_to);
};

#endif
