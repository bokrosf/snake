#ifndef SNAKE_ENGINE_VECTOR2_H
#define SNAKE_ENGINE_VECTOR2_H

class vector2
{
public:
    vector2();
    vector2(float x, float y);
    float x() const;
    float y() const;
    float magnitude() const;
    float square_magnitude() const;
    vector2 normalize() const;
    vector2 points_to(const vector2 &position) const;
    float distance_from(const vector2 &position) const;
    float square_distance_from(const vector2 &position) const;
    vector2 perpendicular() const;
    vector2 absolute() const;
    vector2 truncate() const;
    static vector2 zero();
    static vector2 up();
    static vector2 down();
    static vector2 left();
    static vector2 right();
    friend bool operator==(const vector2 &lhs, const vector2 &rhs);
    vector2 &operator+=(const vector2 &rhs);
    vector2 operator+(const vector2 &rhs) const;
    vector2 &operator-=(const vector2 &rhs);
    vector2 operator-(const vector2 &rhs) const;
    vector2 &operator*=(float rhs);
    vector2 operator*(float rhs) const;
    friend vector2 operator*(float lhs, const vector2 &rhs);
    vector2 &operator/=(float rhs);
    vector2 operator/(float rhs) const;
    vector2 operator-() const;
private:
    float _x;
    float _y;
};

#endif
