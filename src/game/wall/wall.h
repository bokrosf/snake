#ifndef SNAKE_GAME_WALL_WALL_H
#define SNAKE_GAME_WALL_WALL_H

#include <engine/component/behavior.h>
#include <engine/collision/collision_handler.h>
#include <engine/entity.h>
#include <engine/vector2.h>

class wall : public behavior, public collision_handler
{
public:
    wall(entity &attached_to, const vector2 &position, const vector2 &area);
    const vector2 &position() const;
    const vector2 &area() const;
    void collide(const collision &collision) override;
private:
    vector2 _position;
    vector2 _area;
};

#endif
