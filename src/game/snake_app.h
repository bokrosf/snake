#ifndef SNAKE_GAME_SNAKEAPP_H
#define SNAKE_GAME_SNAKEAPP_H

#include <engine/app.h>
#include <engine/app_configuration.h>

class snake_app : public app
{
public:
    snake_app(const app_configuration &configuration);
protected:
    scene *create_start_scene() override;
};

#endif
