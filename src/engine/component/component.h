#ifndef ENGINE_COMPONENT_COMPONENT_H
#define ENGINE_COMPONENT_COMPONENT_H

#include <engine/life_state.h>
#include <engine/messaging/messenger.h>

class entity;
class transform;

class component
{
public:
    virtual ~component() = default;
    void destroy();
    ::life_state life_state() const;
    entity &attached_to() const;
    const ::transform &transform() const;
    ::transform &transform();
protected:
    component(entity &attached_to);
    virtual void detach();
    
    messenger &_messenger;
private:
    ::life_state _life_state;
    entity &_attached_to;

    friend class object_initializer;
};

#endif
