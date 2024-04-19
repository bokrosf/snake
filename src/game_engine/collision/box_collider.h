#ifndef SNAKE_GAMEENGINE_COLLISION_BOXCOLLIDER_H
#define SNAKE_GAMEENGINE_COLLISION_BOXCOLLIDER_H

#include <game_engine/vector2.h>
#include <game_engine/component/component.h>

class box_collider : public component
{
public:
    box_collider(game_object &attached_to, const vector2 &center);
    box_collider(game_object &attached_to, const vector2 &center, const vector2 &area);
    const vector2 &center() const;
    void reposition(const vector2 &center);
    const vector2 &area() const;
private:
    vector2 _center;
    vector2 _area;
};

#endif
