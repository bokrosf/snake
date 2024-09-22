#ifndef SNAKE_GAME_SNAKE_MOVEMENTSYSTEM_H
#define SNAKE_GAME_SNAKE_MOVEMENTSYSTEM_H

#include <vector>
#include <engine/component/component.h>
#include <engine/component/initializable.h>
#include <engine/entity.h>
#include <engine/vector2.h>
#include <game/tile_maze/tile_maze.h>

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

class movement_system : public component, public initializable
{
public:
    movement_system(entity &attached_to);
    void initialize() override;
    segment_correction correct_segment(const vector2 &start, const vector2 &end) const;
    turning_correction correct_turning(const vector2& head_position, const vector2 &turn_direction) const;
private:
    vector2 project_longer_axis(const vector2 &position) const;

    const tile_maze *_tile_maze;
};

#endif