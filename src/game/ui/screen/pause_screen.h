#ifndef SNAKE_GAME_UI_SCREEN_PAUSESCREEN_H
#define SNAKE_GAME_UI_SCREEN_PAUSESCREEN_H

#include <game/ui/screen/menu_screen.h>

class pause_screen : public menu_screen
{
public:
    pause_screen(entity &attached_to, const screen_configuration &configuration);
    void initialize() override;
    void update() override;
protected:
    void confirm() override;
private:
    void resume();
};

#endif
