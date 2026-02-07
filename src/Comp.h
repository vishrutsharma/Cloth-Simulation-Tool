#pragma once
#include <type_traits>

struct IVec2 {
    float x;
    float y;

    IVec2 operator + (const IVec2& vec) const {
        return  { x + vec.x , y + vec.y };
    }

    IVec2& operator += (const IVec2& vec)  {
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
    IVec2 operator * (T scalar) const {
        return { x * scalar , y * scalar };
    } 

};