#ifndef SNAKE_GAME_UI_SCREEN_MENUSCREEN_H
#define SNAKE_GAME_UI_SCREEN_MENUSCREEN_H

#include <string>
#include <vector>
#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <engine/component/updatable.h>
#include <engine/entity.h>
#include <game/ui/screen/screen_configuration.h>

class menu_screen : public behavior, public initializable, public updatable
{
public:
    virtual ~menu_screen() = default;
protected:
    menu_screen(entity &attached_to, const screen_configuration &configuration);
    void add_menu_item(const std::string &image_path);
    unsigned int selected_item_index() const;
    void select_item(unsigned int index);
    void interact();
    virtual void confirm() = 0;

    const screen_configuration _configuration;
    const int _default_rendering_layer;
private:
    std::vector<entity *> _menu_items;
    unsigned int _selected_item_index;
};

#endif
