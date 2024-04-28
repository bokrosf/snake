#ifndef SNAKE_GAME_SNAKEAPP_H
#define SNAKE_GAME_SNAKEAPP_H

#include <engine/app.h>

class snake_app : public app
{
public:
    snake_app();
protected:
    scene *create_start_scene() override;
};

#endif
