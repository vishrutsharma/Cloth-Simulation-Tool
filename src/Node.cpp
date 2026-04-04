#include "Node.h"

Node::Node(FVec2& currentPos,SDL_Color& color,int size,bool isPinned) {
    m_currentPos = currentPos;
    m_prevPos = currentPos;
    m_size = size;
    SetColor(color);
    m_velocity = FVec2{0,0};
    m_rect.w = size;
    m_rect.h = size;
    m_mass = 1;
    m_isPinned = isPinned;
    Update(0.0f);
}

void Node::Update(float dt)
{
    m_rect.x = static_cast<int>(m_currentPos.x - m_size/2);
    m_rect.y = static_cast<int>(m_currentPos.y - m_size/2);
}

void Node::Render(SDL_Renderer* renderer) {
    SDL_Color color = GetColor();
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
    SDL_RenderFillRect(renderer,&GetRect());
}



