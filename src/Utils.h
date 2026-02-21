
#pragma once

#include <random>
#include <cstdlib>
#include <ctime>
#include <SDL.h>

namespace Utils
{
    namespace Random
    {
        inline void Seed()
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
        }

        inline int Int(int maxExclusive)
        {
            return std::rand() % maxExclusive;
        }


        inline int IntRange(int min, int max)
        {
            return min + (std::rand() % (max - min + 1));
        }

        inline float Float01()
        {
            return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        }

        inline SDL_Color GetRandomColorRGB()
        {
            
            SDL_Color color;
            color.r = static_cast<Uint8>(Int(256));
            color.g = static_cast<Uint8>(Int(256));
            color.b = static_cast<Uint8>(Int(256));
            color.a = 255;
            return color;
        }

        inline SDL_Color GetRandomColorHSV(int saturationLevel = 1, int valueLevel = 1)
        {
            float h = Float01() * 360.0f;
            float s =  saturationLevel;
            float v =  valueLevel;
            float c = v * s;               
            float x = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
            float m = v - c;

            float r1, g1, b1;

            if (h < 60)      { r1 = c; g1 = x; b1 = 0; }
            else if (h < 120){ r1 = x; g1 = c; b1 = 0; }
            else if (h < 180){ r1 = 0; g1 = c; b1 = x; }
            else if (h < 240){ r1 = 0; g1 = x; b1 = c; }
            else if (h < 300){ r1 = x; g1 = 0; b1 = c; }
            else             { r1 = c; g1 = 0; b1 = x; }

            SDL_Color color;
            color.r = (Uint8)((r1 + m) * 255);
            color.g = (Uint8)((g1 + m) * 255);
            color.b = (Uint8)((b1 + m) * 255);
            color.a = 255;

            return color;
        }

    }
}