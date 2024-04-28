#ifndef SNAKE_GAME_SNAKE_SNAKECONTROLLER_H
#define SNAKE_GAME_SNAKE_SNAKECONTROLLER_H

#include <game_engine/component/behavior.h>
#include <game_engine/component/updatable.h>
#include "snake.h"

class snake_controller : public behavior, public updatable
{
public:
    snake_controller(entity &attached_to);
    void initialize() override;
    void update() override;
private:
    snake *_snake;
};

#endif
