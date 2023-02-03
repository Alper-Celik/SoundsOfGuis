#pragma once
namespace sog
{
template <typename T = float> struct point2
{
    T x = 0, y = 0;
    point2<T> &operator+=(const point2<T> &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    };
    point2<T> &operator-=(const point2<T> &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    };
    friend point2<T> &operator/=(point2<T> &lhs, const point2<T> &rhs)
    {
        lhs.x /= rhs.x;
        lhs.y /= rhs.y;
        return lhs;
    }
    point2<T> operator+(const point2<T> &other)
    {
        point2<T> _out = *this;
        _out += other;
        return _out;
    };
    point2<T> operator-(const point2<T> &other)
    {
        point2<T> _out = *this;
        _out -= other;
        return _out;
    };

    friend point2<T> operator/(const point2<T> &lhs, const point2<T> &rhs)
    {
        point2<T> out = lhs;
        out /= rhs;
        return out;
    }
    bool operator==(const point2<T> &) const = default;
    bool operator!=(const point2<T> &) const = default;
};
} // namespace sog
