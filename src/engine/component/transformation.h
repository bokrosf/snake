#ifndef ENGINE_COMPONENT_TRANSFORMATION_H
#define ENGINE_COMPONENT_TRANSFORMATION_H

#include <engine/component/component.h>
#include <engine/vector2.h>

class transformation : public component
{
public:
    transformation(entity &attached_to);
    const vector2 &position() const;
    void position(const vector2 &position);
    void translate(const vector2 &translation);
    const vector2 &scale() const;
    void scale(const vector2 &scaling);
private:
    vector2 _position;
    vector2 _scale;
};

#endif
