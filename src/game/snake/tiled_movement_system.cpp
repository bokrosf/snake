#include <cmath>
#include "movement_system.h"
#include "tiled_movement_system.h"

tiled_movement_system::tiled_movement_system(game_object &attached_to, float tile_size)
    : movement_system(attached_to)
    , _tile_size(tile_size)
{
}

segment_correction tiled_movement_system::correct_segments(const vector2 &start, const vector2 &end) const
{
    vector2 start_corrected = tile_center(start);
    vector2 end_corrected = tile_center(end);
    vector2 difference = start_corrected.points_to(end_corrected);
    end_corrected = start_corrected + project_longer_axis(difference);

    return segment_correction { start_corrected, end_corrected };
}

turning_correction tiled_movement_system::correct_turning(const vector2 &head_position, const vector2 &look_direction) const
{
    std::vector<vector2> head_segments = { tile_center(head_position), tile_center(head_position) };

    return turning_correction { head_segments, project_longer_axis(look_direction).normalize() };
}

vector2 tiled_movement_system::tile_center(const vector2 &position) const
{
    vector2 lower_left_corner = vector2(
        static_cast<int>(position.x() / _tile_size) * _tile_size,
        static_cast<int>(position.y() / _tile_size) * _tile_size);

    vector2 center_offset = 0.5 * vector2(_tile_size, _tile_size);

    return lower_left_corner + center_offset;
}

vector2 tiled_movement_system::project_longer_axis(const vector2 &position) const
{
    return std::abs(position.x()) > std::abs(position.y())
        ? vector2(position.x(), 0)
        : vector2(0, position.y());
}
