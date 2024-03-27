#include <cmath>
#include "movement_system.h"
#include "tiled_movement_system.h"

tiled_movement_system::tiled_movement_system(game_object &attached_to, float tile_size)
    : movement_system(attached_to)
    , _tile_size(tile_size)
{
}

segment_correction tiled_movement_system::correct_segments(vector2 start, vector2 end) const
{
    start = tile_center(start);
    end = tile_center(start);
    vector2 difference = start.points_to(end);
    end = start + project_longer_axis(difference);

    return segment_correction { start, end };
}

head_turning_correction tiled_movement_system::correct_head_turning(vector2 head_position, vector2 look_direction) const
{
    std::vector<vector2> head_segments = { tile_center(head_position) };

    return head_turning_correction { head_segments, project_longer_axis(look_direction).normalize() };
}

vector2 tiled_movement_system::tile_center(vector2 position) const
{
    vector2 lower_left_corner = vector2(
        static_cast<int>(position.x() / _tile_size) * _tile_size,
        static_cast<int>(position.y() / _tile_size) * _tile_size);

    vector2 center_offset = 0.5 * vector2(_tile_size, _tile_size);

    return lower_left_corner + center_offset;
}

vector2 tiled_movement_system::project_longer_axis(vector2 position) const
{
    return std::abs(position.x()) > std::abs(position.y())
        ? vector2(position.x(), 0)
        : vector2(0, position.y());
}
