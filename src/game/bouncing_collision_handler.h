#ifndef SNAKE_GAME_BOUNCINGCOLLISIONHANDLER_H
#define SNAKE_GAME_BOUNCINGCOLLISIONHANDLER_H

#include <engine/collision/collision_handler.h>
#include <engine/component/behavior.h>

class bouncing_collision_handler : public behavior, public collision_handler
{
public:
    void collide(const collision &collision) override;
};

#endif