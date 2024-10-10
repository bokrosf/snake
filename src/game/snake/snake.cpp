#include <cmath>
#include <stdexcept>
#include <engine/game_time.h>
#include <game/entity_name.h>
#include <game/game_event.h>
#include <game/snake/snake.h>

#include <engine/logging/logger.h>

ivector2 snake::segment::direction_or(const ivector2 &default_value) const
{
    return begin != end
        ? begin.points_to(end).normalize()
        : default_value;
}

snake::snake(entity &attached_to, const ivector2 &head, const ivector2 &tail)
    : behavior(attached_to)
    , _maze(nullptr)
    , _collider(nullptr)
    , _speed(0)
    , _last_moved(0)
{
    if (head.x != tail.x && head.y != tail.y)
    {
        throw std::invalid_argument("Head and tail must be on the same axis.");
    }

    _segments.push_front(segment{head, tail});
    _head_direction = -_segments.front().direction_or(ivector2::left());
    _last_tail_direction = -_head_direction;
}

void snake::initialize()
{    
    _collider = &attached_to().attached_component<box_collider>();
    _maze = &attached_to().find(entity_name::map)->attached_component<tile_maze>();
}

void snake::start()
{
    transformation().position(_maze->tile_center(head().y, head().x));
    _last_moved = game_time::now();
}

void snake::update()
{
    if (_last_moved > game_time::now())
    {
        return;
    }
    
    float last_moved_delta = game_time::now() - _last_moved;
    unsigned int moved_tiles = last_moved_delta / _speed;
    move_forward(moved_tiles);
    check_self_collision();
}

void snake::look_in_direction(const ivector2 &direction)
{
    if (direction == _head_direction || direction == -_head_direction)
    {
        return;
    }

    if (_segments.front().begin != _segments.front().end)
    {
        _segments.push_front(segment{head(), head()});
    }

    _head_direction = direction;
    move_forward(1);
    _last_moved = game_time::real_now();
    check_self_collision();
}

void snake::adjust_speed(unsigned int tiles_per_second)
{
    _speed = 1.0F / tiles_per_second;
}

std::generator<const snake::segment &> snake::segments() const
{
    for (auto &s : _segments)
    {
        co_yield s;
    }
}

void snake::grow(unsigned int length)
{
    ivector2 tail_direction = _segments.back().direction_or(-_head_direction);

    if (tail_direction == _last_tail_direction)
    {
        _segments.back().end += length * _last_tail_direction;
    }
    else
    {
        ivector2 tail_end = _segments.back().end;
        _segments.push_back(segment{tail_end, tail_end + _last_tail_direction});
    }

}

ivector2 &snake::head()
{
    return _segments.front().begin;
}

void snake::move_forward(unsigned int moved_tiles)
{    
    if (moved_tiles == 0)
    {
        return;
    }
    
    ivector2 movement = moved_tiles * _head_direction;
    head() += movement;
    logger::instance().debug("snake::move_forward|moved: ", moved_tiles, ", dir: (", _head_direction.y, ",", _head_direction.x, ")", "|row: ", head().y, ", col: ", head().x);
    transformation().position(_maze->tile_center(head().y, head().x));
    shrink_tail(moved_tiles);
    _last_moved += moved_tiles * _speed;
}

void snake::shrink_tail(unsigned int moved_tiles)
{
    while (moved_tiles > 0)
    {
        segment &tail = _segments.back();
        unsigned int tail_length = std::round(tail.begin.distance_from(tail.end));
        unsigned int removed_length = std::min(tail_length, moved_tiles);
        _last_tail_direction = tail.begin.points_to(tail.end).normalize();
        tail.end -= removed_length * _last_tail_direction;
        moved_tiles -= removed_length;

        if (_segments.size() > 1 && tail.begin == tail.end)
        {
            _segments.pop_back();
        }
    }
}

void snake::check_self_collision() const
{
    // auto begin = ++_segments.begin();
    // auto end = ++++_segments.begin();

    // while (end != _segments.end())
    // {
    //     vector2 segment = begin->points_to(*end);
    //     vector2 center = *begin + 0.5F * segment;
    //     vector2 area = 0.5F * segment + 0.5F * _thickness * segment.normalize().orthogonal();
    //     vector2 threshold = area.absolute() + _collider->area().absolute();
    //     vector2 difference = center.points_to(_segments.front()).absolute();

    //     if (difference.x < threshold.x && difference.y < threshold.y)
    //     {
    //         _messenger.send(game_event::game_lost);
    //         return;
    //     }

    //     begin = end++;
    // }
}
