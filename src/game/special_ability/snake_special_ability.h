#ifndef SNAKE_GAME_SPECIALABILITY_SNAKESPECIALABILITY_H
#define SNAKE_GAME_SPECIALABILITY_SNAKESPECIALABILITY_H

#include <engine/component/component.h>
#include <game/snake/snake.h>

class snake_special_ability : public component
{
public:
    virtual ~snake_special_ability();
protected:
    snake_special_ability(entity &attached_to);
    ::snake *snake() const;
};

#endif
