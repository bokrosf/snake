#ifndef SNAKE_GAME_FATALCOLLISIONHANDLER_H
#define SNAKE_GAME_FATALCOLLISIONHANDLER_H

#include <engine/collision/collision_handler.h>
#include <engine/component/behavior.h>

class fatal_collision_handler : public behavior, public collision_handler
{
public:
    void collide(const collision &collision) override;
};

#endif