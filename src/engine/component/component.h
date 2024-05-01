#ifndef SNAKE_ENGINE_COMPONENT_COMPONENT_H
#define SNAKE_ENGINE_COMPONENT_COMPONENT_H

#include <engine/life_state.h>
#include <engine/messaging/messenger.h>

class entity;

class component
{
public:
    virtual ~component() = default;
    void destroy();
    life_state life_state() const;
    entity &attached_to() const;
protected:
    component(entity &attached_to);
    virtual void detach();
private:
    ::life_state _life_state;
    entity &_attached_to;
    messenger &_messenger;
};

#endif
