#ifndef SNAKE_ENGINE_COMPONENT_BEHAVIOR_H
#define SNAKE_ENGINE_COMPONENT_BEHAVIOR_H

#include <engine/activatable.h>
#include <engine/component/component.h>

class behavior : public component, public activatable
{
protected:
    behavior(entity &attached_to);
};

#endif
