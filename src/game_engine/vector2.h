#ifndef SNAKE_GAMEENGINE_VECTOR2_H
#define SNAKE_GAMEENGINE_VECTOR2_H

class vector2
{
public:
    vector2();
    vector2(float x, float y);
    friend bool operator==(const vector2 &lhs, const vector2 &rhs);
    vector2 &operator+=(const vector2 &rhs);
    vector2 &operator-=(const vector2 &rhs);
    vector2 &operator*=(float rhs);
    vector2 operator-() const;
    float x() const;
    float y() const;
    float magnitude() const;
    vector2 normalize() const;
    vector2 points_to(const vector2 &position) const;
    float distance_from(const vector2 &position) const;
private:
    float _x;
    float _y;
};

#endif
