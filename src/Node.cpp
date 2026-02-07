#include "Node.h"

Node::Node(IVec2& currentPos,SDL_Color& color) {
    m_currentPos = currentPos;
    m_color = color;
    m_rect.x = m_currentPos.x;
    m_rect.y = m_currentPos.y;
    m_rect.w = NODE_WIDTH;
    m_rect.h = NODE_HEIGHT;
    m_mass = MASS;
}

void Node::Update() {
    m_rect.x = static_cast<int>(m_currentPos.x);
    m_rect.y =  static_cast<int>(m_currentPos.y);
}



