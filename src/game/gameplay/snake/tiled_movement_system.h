#ifndef SNAKE_GAME_GAMEPLAY_SNAKE_TILEDMOVEMENTSYSTEM_H
#define SNAKE_GAME_GAMEPLAY_SNAKE_TILEDMOVEMENTSYSTEM_H

#include "movement_system.h"

class tiled_movement_system : public movement_system
{
public:
    tiled_movement_system(game_object &attached_to, float tile_size);
    segment_correction correct_segments(const vector2 &start, const vector2 &end) const override;
    head_turning_correction correct_head_turning(const vector2 &head_position, const vector2 &look_direction) const override;
private:
    const float _tile_size;
    vector2 tile_center(const vector2 &position) const;
    vector2 project_longer_axis(const vector2 &position) const;
};

#endif