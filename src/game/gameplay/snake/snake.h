#ifndef SNAKE_GAME_GAMEPLAY_SNAKE_SNAKE_H
#define SNAKE_GAME_GAMEPLAY_SNAKE_SNAKE_H

#include <list>
#include <game_engine/vector2.h>
#include <game_engine/gameplay/behavior.h>
#include <game_engine/gameplay/updatable.h>
#include "movement_system.h"

class snake : public behavior
{
public:
    snake(game_object &attached_to);
    void initialize(const vector2 &head, const vector2 &tail);
    void update() override;
    void look_in_direction(const vector2 &direction);
    void change_speed(float speed);
private:
    vector2 _head_direction;
    std::list<vector2> _segments;
    movement_system *_movement_system;
    float _speed;
    void move_forward();
};

#endif