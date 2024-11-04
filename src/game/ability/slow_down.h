#ifndef SNAKE_GAME_ABILITY_SLOWDOWN_H
#define SNAKE_GAME_ABILITY_SLOWDOWN_H

#include <engine/component/initializable.h>
#include <game/ability/ability.h>
#include <game/snake/snake.h>

class slow_down : public ability, public initializable
{
public:
    slow_down(float duration);
    void initialize() override;
    void start() override;
protected:
    void detach() override;
private:
    snake *_snake;
    unsigned int _original_speed;
};

#endif