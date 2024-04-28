#ifndef SNAKE_GAMEENGINE_COMPONENT_COMPONENT_H
#define SNAKE_GAMEENGINE_COMPONENT_COMPONENT_H

#include <game_engine/life_state.h>
#include <game_engine/messaging/messenger.h>

class entity;

class component
{
public:
    virtual ~component() = default;
    virtual void initialize();
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
