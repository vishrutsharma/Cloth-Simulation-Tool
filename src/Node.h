#pragma once
#include "Comp.h"
#include <SDL_rect.h>

#define MASS 1
#define NODE_WIDTH 20
#define NODE_HEIGHT 20

class Node
{
private:
    float m_mass;
    SDL_Rect m_rect;
    SDL_Color m_color;
    int m_size;

public:
    Node(Vec2&,SDL_Color&,int size);
    inline const SDL_Color& GetColor() {return m_color;}
    inline const SDL_Rect& GetRect() {return m_rect;}
    inline const float GetMass() {return m_mass;}
    void Update();
    void SetPos(Vec2& pos);
    Vec2 m_currentPos;
    Vec2 m_prevPos;
    Vec2 m_velocity;
};