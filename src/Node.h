#pragma once
#include "Comp.h"
#include <SDL_rect.h>

#define MASS 40
#define NODE_WIDTH 20
#define NODE_HEIGHT 20

class Node
{
private:
    float m_mass;
    SDL_Rect m_rect;
    SDL_Color m_color;

public:
    Node(IVec2&,SDL_Color&);
    inline const SDL_Color& GetColor() {return m_color;}
    inline const SDL_Rect& GetRect() {return m_rect;}
    inline const float GetMass() {return m_mass;}
    void Update();
    void SetPos(IVec2& pos);
    IVec2 m_currentPos;
    IVec2 m_prevPos;
    IVec2 m_velocity;
};