#ifndef SNAKE_GAME_SNAKEAPP_H
#define SNAKE_GAME_SNAKEAPP_H

#include <game_engine/app.h>

class snake_app : public app
{
public:
    snake_app();
protected:
    void start() override;
};

#endif
