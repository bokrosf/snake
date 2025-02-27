#ifndef SNAKE_GAME_FOOD_FOOD_H
#define SNAKE_GAME_FOOD_FOOD_H

#include <engine/collision/collision_handler.h>
#include <engine/component/behavior.h>
#include <game/snake/snake.h>

class food : public behavior, public collision_handler
{
public:
    food(unsigned int nutritional_value);
    void collide(const collision &collision) final;
protected:
    virtual void eat(snake &snake);
    
    const unsigned int _nutritional_value;
};

#endif
