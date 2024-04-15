#ifndef SNAKE_GAME_SNAKE_MOVEMENTSYSTEM_H
#define SNAKE_GAME_SNAKE_MOVEMENTSYSTEM_H

#include <vector>
#include <game_engine/vector2.h>
#include <game_engine/component/component.h>

struct segment_correction
{
    vector2 start;
    vector2 end;
};

struct turning_correction
{
    std::vector<vector2> head_segments;
    vector2 head_direction;
};

class movement_system : public component
{
public:
    movement_system(game_object &attached_to);
    virtual segment_correction correct_segments(const vector2 &start, const vector2 &end) const = 0;
    virtual turning_correction correct_turning(const vector2& head_position, const vector2 &look_direction) const = 0;
};

#endif