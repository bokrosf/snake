#include <cmath>
#include <stdexcept>
#include <engine/vector2.h>

vector2::vector2()
    : vector2(0, 0)
{
}

vector2::vector2(float x, float y)
    : x(x)
    , y(y)
{
}

float vector2::magnitude() const
{
    return std::sqrt(square_magnitude());
}

float vector2::square_magnitude() const
{
    return x * x + y * y;
}

vector2 vector2::normalize() const
{
    if (*this == zero())
    {
        throw std::logic_error("Zero vector does not have a length. It can not be normalized.");
    }
    
    return (*this) / magnitude();
}

vector2 vector2::points_to(const vector2 &position) const
{
    return position - *this;
}

float vector2::distance_from(const vector2 &position) const
{
    return points_to(position).magnitude();
}

float vector2::square_distance_from(const vector2 &position) const
{
    return points_to(position).square_magnitude();
}

vector2 vector2::orthogonal() const
{
    return vector2(y, -x);
}

vector2 vector2::absolute() const
{
    return vector2(std::abs(x), std::abs(y));
}

vector2 vector2::round() const
{
    return vector2(std::round(x), std::round(y));
}

vector2 vector2::sign() const
{
    return vector2(
        x < 0 ? -1 : 1,
        y < 0 ? -1 : 1);
}

vector2 vector2::zero()
{
    return vector2(0, 0);
}

vector2 vector2::up()
{
    return vector2(0, 1);
}

vector2 vector2::down()
{
    return vector2(0, -1);
}

vector2 vector2::left()
{
    return vector2(-1, 0);
}

vector2 vector2::right()
{
    return vector2(1, 0);
}

bool operator==(const vector2 &lhs, const vector2 &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const vector2 &lhs, const vector2 &rhs)
{
    return !(lhs == rhs);
}

vector2 &vector2::operator+=(const vector2 &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

vector2 vector2::operator+(const vector2 &rhs) const
{
    return vector2(*this) += rhs;
}

vector2 &vector2::operator-=(const vector2 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

vector2 vector2::operator-(const vector2 &rhs) const
{
    return vector2(*this) -= rhs;
}

vector2 &vector2::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;

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

vector2 &vector2::operator/=(float rhs)
{
    x /= rhs;
    y /= rhs;

    return *this;
}

vector2 vector2::operator/(float rhs) const
{
    return vector2(*this) /= rhs;
}

vector2 vector2::operator-() const
{
    return *this * -1;
}
