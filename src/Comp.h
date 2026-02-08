#pragma once
#include <type_traits>

struct Vec2 {
    float x;
    float y;

    Vec2 operator + (const Vec2& vec) const {
        return  { x + vec.x , y + vec.y };
    }

    Vec2& operator += (const Vec2& vec)  {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    template<
        typename T,
        typename = std::enable_if_t<
            std::is_same_v<T, int> || std::is_same_v<T, float>
        >
    >
    Vec2 operator * (T scalar) const {
        return { x * scalar , y * scalar };
    } 

};