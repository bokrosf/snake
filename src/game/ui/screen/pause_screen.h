#ifndef SNAKE_GAME_UI_SCREEN_PAUSESCREEN_H
#define SNAKE_GAME_UI_SCREEN_PAUSESCREEN_H

#include <string>
#include <vector>
#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <engine/component/updatable.h>
#include <engine/entity.h>
#include <game/ui/screen/screen_configuration.h>

class pause_screen : public behavior, public initializable, public updatable
{
public:
    pause_screen(entity &attached_to, const screen_configuration &configuration);
    void initialize() override;
    void update() override;
private:
    void add_menu_item(const std::string &image_path);
    void select_item(size_t index);
    void confirm();
    void resume();

    const screen_configuration _configuration;
    std::vector<entity *> _menu_items;
    size_t _selected_item_index;
};

#endif
