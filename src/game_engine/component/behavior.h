#ifndef SNAKE_GAMEENGINE_COMPONENT_BEHAVIOR_H
#define SNAKE_GAMEENGINE_COMPONENT_BEHAVIOR_H

#include <game_engine/activatable.h>
#include <game_engine/component/component.h>

class behavior : public component, public activatable
{
protected:
    behavior(entity &attached_to);
};

#endif
