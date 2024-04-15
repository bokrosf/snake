#include <stdexcept>
#include <game_engine/game_time.h>
#include "snake.h"

snake::snake(game_object &attached_to, const vector2 &head, const vector2 &tail)
    : behavior(attached_to)
    , _movement_system(nullptr)
    , _speed(0)
{
    if (head.distance_from(tail) <= 0)
    {
        throw std::invalid_argument("Head and tail can not be the same position. Segment's length must be greater than zero.");
    }
    
    _head_direction = vector2::left();
    _segments.push_front(head);
    _segments.push_back(tail);
}

void snake::initialize()
{    
    _movement_system = &attached_to().attached_component<movement_system>();
    segment_correction correction = _movement_system->correct_segments(_segments.front(), _segments.back());
    _head_direction = correction.end.points_to(correction.start).normalize();
    _segments.front() = correction.start;
    _segments.back() = correction.end;
}

void snake::update()
{
    move_forward();
}

void snake::look_in_direction(const vector2 &direction)
{
    turning_correction correction = _movement_system->correct_turning(_segments.front(), direction.normalize());

    if (correction.head_direction == -_head_direction)
    {
        return;
    }

    _head_direction = correction.head_direction;
    _segments.pop_front();

    for (const auto &position : correction.head_segments)
    {
        _segments.push_front(position);
    }
}

void snake::change_speed(float speed)
{
    if (speed <= 0)
    {
        throw std::invalid_argument("Speed must be greater than zero.");
    }

    _speed = speed;
}

const std::list<vector2> &snake::segments() const
{
    return _segments;
}

void snake::move_forward()
{
    float moved_distance = game_time::delta_time() * _speed;
    _segments.front() = moved_distance * _head_direction;
    bool moving_tail = true;

    while (moving_tail)
    {
        vector2 before_last = *(++_segments.rbegin());
        float tail_length = before_last.distance_from(_segments.back());

        if (tail_length > moved_distance)
        {
            vector2 tail_direction = before_last.points_to(_segments.back()).normalize();
            _segments.back() -= moved_distance * tail_direction;
        }
        else
        {
            _segments.pop_back();
        }

        float removed_length = std::min(tail_length, moved_distance);
        moving_tail = moved_distance - removed_length < moved_distance;
        moved_distance -= removed_length;   
    }
}
