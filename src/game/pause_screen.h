#ifndef SNAKE_GAME_PAUSESCREEN_H
#define SNAKE_GAME_PAUSESCREEN_H

#include <engine/component/behavior.h>
#include <engine/component/updatable.h>

class pause_screen : public behavior, public updatable
{
public:
    pause_screen(entity &attached_to);
    void update() override;
};

#endif
