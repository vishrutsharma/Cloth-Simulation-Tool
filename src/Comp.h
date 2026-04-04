#pragma once
#include <ostream>
#include <type_traits>
#include <cstdint>

enum ColorPreset : uint32_t
{
    RED        = 0xFF0000,
    GREEN      = 0x00FF00,
    BLUE       = 0x0000FF,
    WHITE      = 0xFFFFFF,
    BLACK      = 0x000000,
    YELLOW     = 0xFFFF00,
    CYAN       = 0x00FFFF,
    MAGENTA    = 0xFF00FF,
    ORANGE     = 0xFFA500,
    PURPLE     = 0x800080
};

template <typename T>
struct Vec2
{
    T x{};
    T y{};

    Vec2() = default;
    Vec2(T x_, T y_) : x(x_),y(y_){}

    Vec2 operator+(const Vec2& v) const{
        return {v.x + x,v.y + y};
    }

    Vec2 operator-(const Vec2& v) const{
        return {x - v.x,y - v.y};
    }

    template<typename S,typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr Vec2 operator*(S s) const noexcept{
        return { x * s, y * s };
    }

    template<typename S,typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr Vec2& operator*=(S s) noexcept{
        x *= s;
        y *= s;
        return *this;
    }
};

template<typename T, typename S,typename = std::enable_if_t<std::is_arithmetic_v<S>>>
constexpr Vec2<T> operator*(S s, const Vec2<T>& v) noexcept{
    return { v.x * s, v.y * s };
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& v)
{
    os << "Vec2(" << v.x << ", " << v.y << ")";
    return os;
}

using FVec2 = Vec2<float>;
using IVec2 = Vec2<int>;