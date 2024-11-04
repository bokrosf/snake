#ifndef SNAKE_GAME_SNAKE_SNAKE_H
#define SNAKE_GAME_SNAKE_SNAKE_H

#include <generator>
#include <list>
#include <engine/collision/box_collider.h>
#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/component/updatable.h>
#include <engine/time/time_point.h>
#include <engine/vector2.h>
#include <game/tile_maze/tile_maze.h>

class snake : public behavior, public initializable, public startable, public updatable
{
public:
    struct segment
    {
        ivector2 direction_or(const ivector2 &default_value) const;
        
        ivector2 begin;
        ivector2 end;
    };

    snake(const ivector2 &head, const ivector2 &tail);
    void initialize() override;
    void start() override;
    void update() override;
    void move_forward(unsigned int moved_tiles);
    void look_in_direction(const ivector2 &direction);
    unsigned int speed() const;
    void speed(unsigned int tiles_per_second);
    void reverse();
    std::generator<const segment &> segments() const;
    void grow(unsigned int length);
private:
    ivector2 &head();
    void shrink_tail(unsigned int moved_tiles);
    void check_self_collision() const;

    ivector2 _head_direction;
    std::list<segment> _segments;
    tile_maze *_maze;
    box_collider *_collider;
    float _speed;
    time_point _last_moved;
    ivector2 _last_tail_direction;
};

#endif
