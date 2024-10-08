#ifndef SNAKE_GAME_SNAKE_SNAKE_H
#define SNAKE_GAME_SNAKE_SNAKE_H

#include <list>
#include <engine/entity.h>
#include <engine/collision/box_collider.h>
#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/component/updatable.h>
#include <engine/vector2.h>
#include <game/snake/movement_system.h>

class snake : public behavior, public initializable, public startable, public updatable
{
public:
    snake(entity &attached_to, const vector2 &head, const vector2 &tail, float thickness);
    void initialize() override;
    void start() override;
    void update() override;
    void look_in_direction(const vector2 &direction);
    void adjust_speed(float speed);
    const std::list<vector2> &segments() const;
    void grow(float length);
private:
    void move_forward();
    void shrink_tail(float removed_length);
    void check_self_collision() const;

    vector2 _head_direction;
    std::list<vector2> _segments;
    movement_system *_movement_system;
    box_collider *_collider;
    float _speed;
    const float _thickness;
};

#endif
