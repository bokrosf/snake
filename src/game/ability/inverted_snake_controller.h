#ifndef SNAKE_GAME_ABILITY_INVERTEDSNAKECONTROLLER_H
#define SNAKE_GAME_ABILITY_INVERTEDSNAKECONTROLLER_H

#include <engine/component/behavior.h>
#include <game/ability/ability.h>

class inverted_snake_controller : public ability
{
public:
    inverted_snake_controller(entity &attached_to, float duration);
    void initialize() override;
    void start() override;
    void update_effect() override;
protected:
    void detach() override;
private:
    behavior *_original_controller;
};

#endif