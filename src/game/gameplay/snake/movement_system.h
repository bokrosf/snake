#ifndef SNAKE_GAME_GAMEPLAY_SNAKE_MOVEMENTSYSTEM_H
#define SNAKE_GAME_GAMEPLAY_SNAKE_MOVEMENTSYSTEM_H

#include <vector>
#include "../../../game_engine/vector2.h"
#include "../../../game_engine/gameplay/component.h"

struct segment_correction
{
    vector2 start;
    vector2 end;
};

struct head_turning_correction
{
    std::vector<vector2> head_segments;
    vector2 head_direction;
};

class movement_system : public component
{
public:
    movement_system(game_object &attached_to);
    virtual segment_correction correct_segments(vector2 start, vector2 end) const = 0;
    virtual head_turning_correction correct_head_turning(vector2 head_position, vector2 look_direction) const = 0;
};

#endif