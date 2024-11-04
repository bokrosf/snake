#ifndef SNAKE_GAME_UI_BORDER_H
#define SNAKE_GAME_UI_BORDER_H

#include <engine/component/component.h>
#include <engine/vector2.h>

class border : public component
{
public:
    border();
    const vector2 &inner_area() const;
    void inner_area(const vector2 &value);
    float thickness() const;
    void thickness(float value);
private:
    vector2 _inner_area;
    float _thickness;
};

#endif
