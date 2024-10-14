#ifndef SNAKE_GAME_ABILITY_ABILITY_H
#define SNAKE_GAME_ABILITY_ABILITY_H

#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/component/updatable.h>
#include <game/snake/snake.h>

class ability : public behavior, public initializable, public startable, public updatable
{
public:
    void initialize() override;
    void start() override;
    void update() override final;
protected:
    ability(entity &attached_to, float duration);
    ::snake &snake() const;
    virtual void update_effect();
private:
    const float _duration;
    float _expiration;
    ::snake *_snake;
};

#endif