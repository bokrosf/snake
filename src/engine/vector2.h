#ifndef ENGINE_VECTOR2_H
#define ENGINE_VECTOR2_H

#include <cmath>
#include <cstddef>
#include <functional>
#include <stdexcept>

template<typename T>
struct vector;

typedef vector<float> vector2;
typedef vector<int> ivector2;
typedef vector<unsigned int> uivector2;

template<typename T>
bool operator==(const vector<T> &lhs, const vector<T> &rhs);

template<typename Scalar, typename T>
vector<T> operator*(Scalar lhs, const vector<T> &rhs);

template<typename T>
struct vector
{
    vector();
    vector(T x, T y);
    float magnitude() const;
    float square_magnitude() const;
    vector normalize() const;
    vector points_to(const vector &position) const;
    float distance_from(const vector &position) const;
    float square_distance_from(const vector &position) const;
    vector orthogonal() const;
    vector absolute() const;
    vector round() const;
    vector trunc() const;
    vector sign() const;
    static vector zero();
    static vector up();
    static vector down();
    static vector left();
    static vector right();

    template<typename S>
    friend bool operator==(const vector<S> &lhs, const vector<S> &rhs);

    vector &operator+=(const vector &rhs);
    vector operator+(const vector &rhs) const;
    vector &operator-=(const vector &rhs);
    vector operator-(const vector &rhs) const;
    vector &operator*=(T rhs);
    vector operator*(T rhs) const;

    template<typename Scalar, T>
    friend vector<T> operator*(Scalar lhs, const vector<T> &rhs);
    
    vector &operator/=(T rhs);
    vector operator/(T rhs) const;
    vector operator-() const;

    T x;
    T y;

    struct std::hash<vector>;
};

typedef vector<float> vector2;
typedef vector<int> ivector2;
typedef vector<unsigned int> uivector2;

template<typename T>
vector<T>::vector()
    : vector(0, 0)
{
}

template<typename T>
vector<T>::vector(T x, T y)
    : x(x)
    , y(y)
{
}

template<typename T>
float vector<T>::magnitude() const
{
    return std::sqrt(square_magnitude());
}

template<typename T>
float vector<T>::square_magnitude() const
{
    return x * x + y * y;
}

template<typename T>
vector<T> vector<T>::normalize() const
{
    if (*this == zero())
    {
        throw std::logic_error("Zero vector does not have a length. It can not be normalized.");
    }
    
    return (*this) / magnitude();
}

template<typename T>
vector<T> vector<T>::points_to(const vector<T> &position) const
{
    return position - *this;
}

template<typename T>
float vector<T>::distance_from(const vector<T> &position) const
{
    return points_to(position).magnitude();
}

template<typename T>
float vector<T>::square_distance_from(const vector<T> &position) const
{
    return points_to(position).square_magnitude();
}

template<typename T>
vector<T> vector<T>::orthogonal() const
{
    return vector<T>(y, -x);
}

template<typename T>
vector<T> vector<T>::absolute() const
{
    return vector<T>(std::abs(x), std::abs(y));
}

template<typename T>
vector<T> vector<T>::round() const
{
    return vector<T>(std::round(x), std::round(y));
}

template<typename T>
vector<T> vector<T>::trunc() const
{
    return vector<T>(std::trunc(x), std::trunc(y));
}

template<typename T>
vector<T> vector<T>::sign() const
{
    return vector<T>(
        x < 0 ? -1 : 1,
        y < 0 ? -1 : 1);
}

template<typename T>
vector<T> vector<T>::zero()
{
    return vector<T>(0, 0);
}

template<typename T>
vector<T> vector<T>::up()
{
    return vector<T>(0, 1);
}

template<typename T>
vector<T> vector<T>::down()
{
    return vector<T>(0, -1);
}

template<typename T>
vector<T> vector<T>::left()
{
    return vector<T>(-1, 0);
}

template<typename T>
vector<T> vector<T>::right()
{
    return vector<T>(1, 0);
}

template<typename T>
bool operator==(const vector<T> &lhs, const vector<T> &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template<typename T>
bool operator!=(const vector<T> &lhs, const vector<T> &rhs)
{
    return !(lhs == rhs);
}

template<typename T>
vector<T> &vector<T>::operator+=(const vector<T> &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

template<typename T>
vector<T> vector<T>::operator+(const vector<T> &rhs) const
{
    return vector<T>(*this) += rhs;
}

template<typename T>
vector<T> &vector<T>::operator-=(const vector<T> &rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

template<typename T>
vector<T> vector<T>::operator-(const vector<T> &rhs) const
{
    return vector<T>(*this) -= rhs;
}

template<typename T>
vector<T> &vector<T>::operator*=(T rhs)
{
    x *= rhs;
    y *= rhs;

    return *this;
}

template<typename T>
vector<T> vector<T>::operator*(T rhs) const
{
    return vector<T>(*this) *= rhs;
}

template<typename Scalar, typename T>
vector<T> operator*(Scalar lhs, const vector<T> &rhs)
{
    return vector<T>(rhs) *= lhs;
}

template<typename T>
vector<T> &vector<T>::operator/=(T rhs)
{
    x /= rhs;
    y /= rhs;

    return *this;
}

template<typename T>
vector<T> vector<T>::operator/(T rhs) const
{
    return vector<T>(*this) /= rhs;
}

template<typename T>
vector<T> vector<T>::operator-() const
{
    return *this * -1;
}

template<>
struct std::hash<ivector2>
{
    std::size_t operator()(const ivector2 &v) const noexcept
    {
        std::hash<int> hash;

        return hash(v.x) * hash(v.x) + hash(v.y);
    }
};

#endif
