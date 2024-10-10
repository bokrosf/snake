#ifndef SNAKE_GAME_TILEMAZE_TILEPOSITION_H
#define SNAKE_GAME_TILEMAZE_TILEPOSITION_H

#include <cstddef>
#include <functional>

struct tile_position
{
    tile_position();
    tile_position(unsigned int row, unsigned int column);
    bool operator==(const tile_position &other) const;
    
    unsigned int row;
    unsigned int column;

    friend struct std::hash<tile_position>;
};

template<>
struct std::hash<tile_position>
{
    size_t operator()(const tile_position &position) const noexcept
    {
        std::hash<unsigned int> hash;

        return hash(position.row) * hash(position.row) + hash(position.column);
    }
};

#endif
