#ifndef SNAKE_GAME_SNAKE_SNAKE_H
#define SNAKE_GAME_SNAKE_SNAKE_H

#include <list>
#include <game_engine/vector2.h>
#include <game_engine/collision/box_collider.h>
#include <game_engine/component/behavior.h>
#include <game_engine/component/updatable.h>
#include "movement_system.h"

class snake : public behavior, public updatable
{
public:
    snake(game_object &attached_to, const vector2 &head, const vector2 &tail);
    void initialize() override;
    void update() override;
    void look_in_direction(const vector2 &direction);
    void adjust_speed(float speed);
    const std::list<vector2> &segments() const;
    void grow(float length);
private:
    vector2 _head_direction;
    std::list<vector2> _segments;
    movement_system *_movement_system;
    box_collider *_collider;
    float _speed;
    void move_forward();
    void shrink_tail(float removed_length);
};

#endif
