#ifndef SNAKE_GAME_UI_SCREEN_PAUSESCREEN_H
#define SNAKE_GAME_UI_SCREEN_PAUSESCREEN_H

#include <array>
#include <string>
#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <engine/component/updatable.h>
#include <engine/entity.h>

class pause_screen : public behavior, public initializable, public updatable
{
public:
    pause_screen(entity &attached_to);
    void initialize() override;
    void update() override;
private:
    enum class menu_option
    {
        resume = 0,
        exit
    };

    void add_menu_item(menu_option option, const std::string &image_path);
    void select_item(size_t index);
    void confirm();
    void resume();

    std::array<entity *, 2> _menu_items;
    size_t _selected_item_index;
};

#endif
