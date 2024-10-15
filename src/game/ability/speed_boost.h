#ifndef SNAKE_GAME_ABILITY_SPEEDBOOST_H
#define SNAKE_GAME_ABILITY_SPEEDBOOST_H

#include <game/ability/ability.h>

class speed_boost : public ability
{
public:
    speed_boost(entity &attached_to, float duration);
    void start() override;
protected:
    void detach() override;
private:
    unsigned int _original_speed;
};

#endif