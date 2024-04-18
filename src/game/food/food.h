#ifndef SNAKE_GAME_FOOD_FOOD_H
#define SNAKE_GAME_FOOD_FOOD_H

#include <game_engine/component/behavior.h>
#include <game_engine/vector2.h>
#include <game/snake/snake.h>

class food : public behavior
{
public:
    const vector2 &position() const;
    virtual void eat(snake &snake) = 0;
protected:
    food(game_object &attached_to, const vector2 &position);
private:
    vector2 _position;
};

#endif
