#ifndef SNAKE_GAME_WALL_WALL_H
#define SNAKE_GAME_WALL_WALL_H

#include <game_engine/component/behavior.h>
#include <game_engine/vector2.h>

class wall : public behavior
{
public:
    wall(entity &attached_to, const vector2 &position, const vector2 &area);
    const vector2 &position() const;
    const vector2 &area() const;
private:
    vector2 _position;
    vector2 _area;
};

#endif
