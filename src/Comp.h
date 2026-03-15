#pragma once
#include <ostream>
#include <type_traits>

template <typename T>
struct Vec2
{
    T x{};
    T y{};

    Vec2() = default;
    Vec2(T x_, T y_) : x(x_),y(y_){}

    Vec2& operator+(const Vec2& v){
        return {v.x + x,v.y + y};
    }

    Vec2& operator-(const Vec2& v){
        return {v.x - x,v.y - y};
    }

    template<typename S,typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    constexpr Vec2& operator*(S s) const noexcept{
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
constexpr Vec2<T>& operator*(S s, const Vec2<T>& v) noexcept{
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