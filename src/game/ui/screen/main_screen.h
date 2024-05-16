#ifndef SNAKE_GAME_UI_SCREEN_MAINSCREEN_H
#define SNAKE_GAME_UI_SCREEN_MAINSCREEN_H

#include <game/ui/screen/menu_screen.h>

class main_screen : public menu_screen
{
public:
    main_screen(entity &attached_to, const screen_configuration &configuration);
    void initialize() override;
    void update() override;
protected:
    void confirm() override;
};

#endif
