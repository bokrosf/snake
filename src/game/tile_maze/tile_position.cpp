#include <game/tile_maze/tile_position.h>

tile_position::tile_position()
    : tile_position(0, 0)
{
}

tile_position::tile_position(unsigned int row, unsigned int column)
    : row(row)
    , column(column)
{
}

bool tile_position::operator==(const tile_position &rhs) const
{
    return row == rhs.row && column == rhs.column;
}
