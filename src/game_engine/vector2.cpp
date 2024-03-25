#include <cmath>
#include "vector2.h"

vector2::vector2()
    : vector2(0, 0)
{
}

vector2::vector2(float x, float y)
    : _x(x)
    , _y(y)
{
}

bool operator==(const vector2 &lhs, const vector2 &rhs)
{
    return lhs._x == rhs._x && lhs._y == rhs._y;
}

bool operator!=(const vector2 &lhs, const vector2 &rhs)
{
    return !(lhs == rhs);
}

vector2 &vector2::operator+=(const vector2 &rhs)
{
    _x += rhs._x;
    _y += rhs._y;

    return *this;
}

vector2 vector2::operator+(const vector2 &rhs) const
{
    return vector2(*this) += rhs;
}

vector2 &vector2::operator-=(const vector2 &rhs)
{
    _x -= rhs._x;
    _y -= rhs._y;

    return *this;
}

vector2 vector2::operator-(const vector2 &rhs) const
{
    return vector2(*this) -= rhs;
}

vector2 &vector2::operator*=(float rhs)
{
    _x *= rhs;
    _y *= rhs;

    return *this;
}

vector2 vector2::operator*(float rhs) const
{
    return vector2(*this) *= rhs;
}

vector2 operator*(float lhs, const vector2 &rhs)
{
    return vector2(rhs) *= lhs;
}

vector2 vector2::operator-() const
{
    return *this * -1;
}

float vector2::x() const
{
    return _x;
}

float vector2::y() const
{
    return _y;
}

float vector2::magnitude() const
{
    return std::sqrt(_x * _x + _y * _y);
}

vector2 vector2::normalize() const
{
    return *this * (1 / magnitude());
}

vector2 vector2::points_to(const vector2 &position) const
{
    return position - *this;
}

float vector2::distance_from(const vector2 &position) const
{
    return points_to(position).magnitude();
}

vector2 vector2::zero()
{
    return vector2(0, 0);
}

vector2 vector2::up()
{
    return vector2(0, 1);
}

vector2 vector2::left()
{
    return vector2(-1, 0);
}

vector2 vector2::right()
{
    return vector2(1, 0);
}
