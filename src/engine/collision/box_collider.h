#ifndef ENGINE_COLLISION_BOXCOLLIDER_H
#define ENGINE_COLLISION_BOXCOLLIDER_H

#include <engine/component/behavior.h>
#include <engine/vector2.h>

class box_collider : public behavior
{
public:
    box_collider();
    box_collider(const vector2 &area);
    const vector2 &area() const;
    void area(const vector2 area);
private:
    vector2 _area;
};

#endif
