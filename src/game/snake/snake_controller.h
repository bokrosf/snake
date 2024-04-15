#ifndef SNAKE_GAME_SNAKE_SNAKECONTROLLER_H
#define SNAKE_GAME_SNAKE_SNAKECONTROLLER_H

#include <game_engine/component/behavior.h>
#include "snake.h"

class snake_controller : public behavior
{
public:
    snake_controller(game_object &attached_to);
    void initialize() override;
    void update() override;
private:
    snake *_snake;
};

#endif
