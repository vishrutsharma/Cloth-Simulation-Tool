#pragma once
#include "Comp.h"
#include <SDL_rect.h>
#include <SDL_render.h>


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
    Node(FVec2&,SDL_Color&,int size,bool);
    inline const SDL_Color& GetColor() {return m_color;}
    inline const SDL_Rect& GetRect() {return m_rect;}
    inline const float GetMass() {return m_mass;}
    void Render(SDL_Renderer*);
    void Update(float dt);
    void SetPos(FVec2& pos);
    FVec2 m_currentPos;
    FVec2 m_prevPos;
    FVec2 m_velocity;
    bool m_isPinned;
};