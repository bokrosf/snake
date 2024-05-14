#ifndef ENGINE_COMPONENT_TRANSFORMATION_H
#define ENGINE_COMPONENT_TRANSFORMATION_H

#include <engine/component/component.h>
#include <engine/vector2.h>

class transformation : public component
{
public:
    transformation(entity &attached_to);
    void translate(const vector2 &translation);
private:
    vector2 _position;
};

#endif
