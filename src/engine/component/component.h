#ifndef ENGINE_COMPONENT_COMPONENT_H
#define ENGINE_COMPONENT_COMPONENT_H

#include <engine/life_state.h>
#include <engine/messaging/messenger.h>

class entity;
class object_initializer;

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
    
    messenger &_messenger;
private:
    friend object_initializer;
    
    ::life_state _life_state;
    entity &_attached_to;
};

#endif
