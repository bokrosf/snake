#ifndef SNAKE_GAME_SNAKE_MOVEMENTSYSTEM_H
#define SNAKE_GAME_SNAKE_MOVEMENTSYSTEM_H

#include <vector>
#include <engine/component/component.h>
#include <engine/vector2.h>

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
    movement_system(entity &attached_to);
    virtual segment_correction correct_segments(const vector2 &start, const vector2 &end) const = 0;
    virtual turning_correction correct_turning(const vector2& head_position, const vector2 &turn_direction) const = 0;
};

#endif