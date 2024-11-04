#ifndef SNAKE_GAME_ABILITY_SPEEDBOOST_H
#define SNAKE_GAME_ABILITY_SPEEDBOOST_H

#include <engine/component/initializable.h>
#include <game/ability/ability.h>
#include <game/snake/snake.h>

class speed_boost : public ability, public initializable
{
public:
    speed_boost(float duration);
    void initialize() override;
    void start() override;
protected:
    void detach() override;
private:
    snake *_snake;
    unsigned int _original_speed;
};

#endif