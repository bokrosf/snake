#include <stdexcept>
#include <engine/game_time.h>
#include <game/game_event.h>
#include <game/snake/snake.h>

snake::snake(entity &attached_to, const vector2 &head, const vector2 &tail, float thickness)
    : behavior(attached_to)
    , _movement_system(nullptr)
    , _collider(nullptr)
    , _speed(0)
    , _thickness(thickness)
{
    if (_thickness < 0)
    {
        throw std::invalid_argument("Thickness must be greater than or equal to zero.");
    }

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
    _collider = &attached_to().attached_component<box_collider>();
    _movement_system = &attached_to().attached_component<movement_system>();
}

void snake::start()
{
    segment_correction correction = _movement_system->correct_segments(_segments.front(), _segments.back());
    _head_direction = correction.end.points_to(correction.start).normalize();
    _segments.front() = correction.start;
    _segments.back() = correction.end;
    transformation().position(_segments.front());
}

void snake::update()
{
    move_forward();
    check_self_collision();
}

void snake::look_in_direction(const vector2 &direction)
{
    turning_correction correction = _movement_system->correct_turning(_segments.front(), direction.normalize());

    if (correction.head_direction == _head_direction || correction.head_direction == -_head_direction)
    {
        return;
    }

    _head_direction = correction.head_direction;
    _collider->area(vector2(_collider->area().y(), _collider->area().x()));
    float original_head_length = _segments.cbegin()->distance_from(*++_segments.cbegin());
    _segments.pop_front();
    float new_head_length = 0;

    for (const auto &position : correction.head_segments)
    {
        new_head_length += _segments.cbegin()->distance_from(position);
        _segments.push_front(position);
    }

    transformation().position(_segments.front());
    float difference = new_head_length - original_head_length;

    if (difference > 0)
    {
        shrink_tail(difference);
    }

    check_self_collision();
}

void snake::adjust_speed(float speed)
{
    if (speed < 0)
    {
        throw std::invalid_argument("Speed must be greater than or equal to zero.");
    }

    _speed = speed;
}

const std::list<vector2> &snake::segments() const
{
    return _segments;
}

void snake::grow(float length)
{
    vector2 tail_direction = (++_segments.crbegin())->points_to(*_segments.crbegin()).normalize();
    _segments.back() += length * tail_direction;
}

void snake::move_forward()
{
    float moved_distance = game_time::delta_time() * _speed;
    transformation().translate(moved_distance * _head_direction);
    _segments.front() = transformation().position();
    shrink_tail(moved_distance);
}

void snake::shrink_tail(float cut_off_length)
{
    bool shrinking = true;

    while (shrinking)
    {
        vector2 before_last = *(++_segments.rbegin());
        float tail_length = before_last.distance_from(_segments.back());

        if (tail_length > cut_off_length)
        {
            vector2 tail_direction = before_last.points_to(_segments.back()).normalize();
            _segments.back() -= cut_off_length * tail_direction;
        }
        else
        {
            _segments.pop_back();
        }

        float removed_length = std::min(tail_length, cut_off_length);
        shrinking = cut_off_length - removed_length < cut_off_length;
        cut_off_length -= removed_length;   
    }
}

void snake::check_self_collision() const
{
    auto end = ++_segments.begin();
    auto start = end++;

    while (end != _segments.end())
    {
        vector2 segment = start->points_to(*end);
        vector2 center = *start + 0.5F * segment;
        vector2 area = 0.5F * segment + 0.5F * _thickness * segment.normalize().perpendicular();
        vector2 threshold = area.absolute() + _collider->area().absolute();
        vector2 difference = center.points_to(_segments.front()).absolute();

        if (difference.x() < threshold.x() && difference.y() < threshold.y())
        {
            _messenger.send(game_event::game_lost);
            return;
        }

        start = end++;
    }
}
