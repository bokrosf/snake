#include <cmath>
#include <game/entity_name.h>
#include <game/snake/movement_system.h>

movement_system::movement_system(entity &attached_to)
    : component(attached_to)
    , _tile_maze(nullptr)
{
}

void movement_system::initialize()
{
    _tile_maze = &attached_to().find(entity_name::map)->attached_component<tile_maze>();
}

segment_correction movement_system::correct_segments(const vector2 &start, const vector2 &end) const
{
    vector2 start_corrected = _tile_maze->tile_center(start);
    vector2 end_corrected = _tile_maze->tile_center(end);
    vector2 difference = start_corrected.points_to(end_corrected);
    end_corrected = start_corrected + project_longer_axis(difference);

    return segment_correction{start_corrected, end_corrected};
}

turning_correction movement_system::correct_turning(const vector2 &head_position, const vector2 &turn_direction) const
{
    vector2 break_point = _tile_maze->tile_center(head_position);
    vector2 corrected_look_direction = project_longer_axis(turn_direction).normalize();
    vector2 corrected_head_position = break_point + (0.5F * _tile_maze->tile_size() * corrected_look_direction);
    std::vector<vector2> head_segments = { break_point, corrected_head_position };

    return turning_correction{head_segments, corrected_look_direction};
}

vector2 movement_system::project_longer_axis(const vector2 &position) const
{
    return std::abs(position.x()) > std::abs(position.y())
        ? vector2(position.x(), 0)
        : vector2(0, position.y());
}
