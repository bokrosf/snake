#ifndef SNAKE_GAMEENGINE_COMPONENT_BEHAVIOR_H
#define SNAKE_GAMEENGINE_COMPONENT_BEHAVIOR_H

#include <game_engine/activatable.h>
#include "component.h"

class behavior : public component, public activatable
{
protected:
    behavior(game_object &attached_to);
};

#endif
