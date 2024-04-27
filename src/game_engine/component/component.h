#ifndef SNAKE_GAMEENGINE_COMPONENT_COMPONENT_H
#define SNAKE_GAMEENGINE_COMPONENT_COMPONENT_H

#include <game_engine/life_state.h>
#include <game_engine/messaging/messenger.h>

class game_object;

class component
{
public:
    virtual ~component() = default;
    virtual void initialize();
    void destroy();
    life_state life_state() const;
    game_object &attached_to() const;
protected:
    component(game_object &attached_to);
    virtual void detach();
private:
    ::life_state _life_state;
    game_object &_attached_to;
    messenger &_messenger;
};

#endif
