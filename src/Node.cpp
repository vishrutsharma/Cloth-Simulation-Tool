#include "Node.h"

Node::Node(Vec2& currentPos,SDL_Color& color,int size) {
    m_currentPos = currentPos;
    m_prevPos = currentPos;
    m_size = size;
    m_color = color;
    m_velocity = Vec2{0,0};
    m_rect.w = size;
    m_rect.h = size;
    m_rect.x = m_currentPos.x;
    m_rect.y = m_currentPos.y;
    m_mass = MASS;
}

void Node::Update() {
    m_rect.x = static_cast<int>(m_currentPos.x);
    m_rect.y =  static_cast<int>(m_currentPos.y);
}



