#ifndef SNAKE_GAME_ABILITY_ABILITY_H
#define SNAKE_GAME_ABILITY_ABILITY_H

#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/component/updatable.h>
#include <engine/entity.h>

class ability : public behavior, public startable, public updatable
{
public:
    void start() override;
    void update() override;
protected:
    ability(entity &attached_to, float duration);
private:
    const float _duration;
    float _expiration;
};

#endif