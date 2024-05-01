#ifndef SNAKE_GAME_SNAKE_TILEDMOVEMENTSYSTEM_H
#define SNAKE_GAME_SNAKE_TILEDMOVEMENTSYSTEM_H

#include <engine/component/initializable.h>
#include <engine/entity.h>
#include <game/snake/movement_system.h>
#include <game/tile_maze.h>

class tiled_movement_system : public movement_system, public initializable
{
public:
    tiled_movement_system(entity &attached_to);
    void initialize() override;
    segment_correction correct_segments(const vector2 &start, const vector2 &end) const override;
    turning_correction correct_turning(const vector2 &head_position, const vector2 &turn_direction) const override;
private:
    vector2 project_longer_axis(const vector2 &position) const;
    
    const tile_maze *_tile_maze;
};

#endif