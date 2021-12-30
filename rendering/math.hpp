#pragma once

template <class T>
struct vec2
{
    T x, y;
    constexpr vec2() : x{},y{}{}
    constexpr vec2(T _x, T _y) : x{_x},y{_y}{}
    
    constexpr vec2 operator+(const vec2& rhs) const { return vec2{x + rhs.x, y + rhs.y}; }
    constexpr vec2 operator-(const vec2& rhs) const { return vec2{x - rhs.x, y - rhs.y}; }
    constexpr vec2 operator*(const T &rhs) const { return vec2{x * rhs, y * rhs}; }
    constexpr vec2 operator/(const T &rhs) const { return vec2{x / rhs, y / rhs}; }

    constexpr vec2& operator+=(const vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    constexpr vec2& operator-=(const vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    constexpr vec2& operator*=(const T &rhs) { x *= rhs; y *= rhs; return *this; }
    constexpr vec2& operator/=(const T &rhs) { x /= rhs; y /= rhs; return *this; }

    constexpr bool operator==(const vec2& rhs) const { return x == rhs.x and y == rhs.y; }
    constexpr bool operator!=(const vec2& rhs) const { return x != rhs.x or y != rhs.y; }
};

