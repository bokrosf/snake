#ifndef SNAKE_GAMEENGINE_COMPONENT_COMPONENT_H
#define SNAKE_GAMEENGINE_COMPONENT_COMPONENT_H

#include <game_engine/game_object.h>

class game_object;

class component
{
public:
    virtual ~component();
    virtual void initialize();
    void destroy();
    game_object &attached_to() const;
protected:
    component(game_object &attached_to);
private:
    game_object &_attached_to;
};

#endif
