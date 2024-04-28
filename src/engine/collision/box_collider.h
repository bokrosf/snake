#ifndef SNAKE_ENGINE_COLLISION_BOXCOLLIDER_H
#define SNAKE_ENGINE_COLLISION_BOXCOLLIDER_H

#include <engine/component/behavior.h>
#include <engine/vector2.h>

class box_collider : public behavior
{
public:
    box_collider(entity &attached_to, const vector2 &center);
    box_collider(entity &attached_to, const vector2 &center, const vector2 &area);
    const vector2 &center() const;
    void reposition(const vector2 &center);
    const vector2 &area() const;
private:
    vector2 _center;
    vector2 _area;
};

#endif