#ifndef ENGINE_VECTOR2_H
#define ENGINE_VECTOR2_H

#include <functional>

struct vector2
{
    vector2();
    vector2(float x, float y);
    float magnitude() const;
    float square_magnitude() const;
    vector2 normalize() const;
    vector2 points_to(const vector2 &position) const;
    float distance_from(const vector2 &position) const;
    float square_distance_from(const vector2 &position) const;
    vector2 orthogonal() const;
    vector2 absolute() const;
    vector2 round() const;
    vector2 sign() const;
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

    float x;
    float y;

    friend struct std::hash<vector2>;
};

template<>
struct std::hash<vector2>
{
    size_t operator()(const vector2 &v) const noexcept
    {
        std::hash<float> hash;

        return hash(v.x) * hash(v.x) + hash(v.y);
    }
};

#endif
