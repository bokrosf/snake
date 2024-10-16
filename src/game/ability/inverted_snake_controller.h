#ifndef SNAKE_GAME_ABILITY_INVERTEDSNAKECONTROLLER_H
#define SNAKE_GAME_ABILITY_INVERTEDSNAKECONTROLLER_H

#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <game/ability/ability.h>
#include <game/snake/snake.h>

class inverted_snake_controller : public ability, public initializable
{
public:
    inverted_snake_controller(entity &attached_to, float duration);
    void initialize() override;
    void start() override;
    void update_effect() override;
protected:
    void detach() override;
private:
    snake *_snake;
    behavior *_original_controller;
};

#endif