#ifndef SNAKE_GAMEENGINE_GAMEPLAY_COMPONENT_H
#define SNAKE_GAMEENGINE_GAMEPLAY_COMPONENT_H

class game_object;

class component
{
public:
    ~component();
    game_object &attached_to() const;
protected:
    component(game_object &attached_to);
private:
    game_object &_attached_to;
};

#endif
