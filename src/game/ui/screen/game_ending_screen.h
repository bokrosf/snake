#ifndef SNAKE_GAME_UI_SCREEN_GAMEENDINGSCREEN_H
#define SNAKE_GAME_UI_SCREEN_GAMEENDINGSCREEN_H

#include <game/ui/screen/screen_configuration.h>
#include <game/ui/screen/menu_screen.h>

class game_ending_screen : public menu_screen
{
public:
    game_ending_screen(const screen_configuration &configuration, bool won);
    void initialize() override;
    void update() override;
protected:
    void confirm() override;
private:
    const bool _won;
};

#endif
