#include "Cloth.h"
#include <cmath>
#include "Utils.h"

Cloth :: Cloth() {
    m_SimulationTimeTick = 0;
}

void Cloth :: Build(){
    m_clothRect.w = m_clothWidth;
    m_clothRect.h = m_clothHeight;
    m_clothRect.x = static_cast<int>(m_position.x) - m_clothWidth/2;
    m_clothRect.y = static_cast<int>(m_position.y) - m_clothHeight/2;
    int resX = floor((m_clothWidth + m_nodesGap)/(m_nodeSize + m_nodesGap));
    int resY = floor((m_clothHeight + m_nodesGap)/(m_nodeSize + m_nodesGap));
    m_nodes.clear();
    m_nodes.reserve(resX * resY);
    
    int stepSize = m_nodeSize + m_nodesGap;
    int startX =  static_cast<int>(m_clothRect.x + m_nodeSize * 0.5f);
    int startY =  static_cast<int>(m_clothRect.y + m_nodeSize * 0.5f);

    for(int y = 0; y < resY; y++)
    {
        for(int x = 0; x < resX; x++)
        {
            float yPos =  startY + y * stepSize;
            float xPos =  startX + x * stepSize;
            Vec2 pos {xPos,yPos};
            SDL_Color color {Utils::Random::GetRandomColorHSV()};
            Node node{pos,color,m_nodeSize};
            m_nodes.push_back(node);
        }
    }    
}


void Cloth :: Update(float dt) {
    if(m_nodes.size() <=0)
        return;
    
    // currently the mass is same for all nodes
    // later it will vary based on user input
    Vec2 force {0,FORCE};
    if(m_SimulationTimeTick <= 100) {
        m_SimulationTimeTick += dt;
        for(Node& node : m_nodes){
            Vec2 acceleration = Vec2{force.x/node.GetMass(),force.y/node.GetMass()};
            const Vec2 prevPos = node.m_currentPos;    
            node.m_currentPos.x = 2 * node.m_currentPos.x - node.m_prevPos.x + acceleration.x * (dt * dt);
            node.m_currentPos.y = 2 * node.m_currentPos.y - node.m_prevPos.y + acceleration.y * (dt * dt);
            node.m_prevPos.x = prevPos.x;
            node.m_prevPos.y = prevPos.y;
            node.Update();
        }
    }
    else{
        m_SimulationTimeTick = 0;
    }
}

void Cloth :: Render() {
    if(!m_renderer)
        return;

    SDL_SetRenderDrawColor(m_renderer,245,122,24,255);
    SDL_RenderDrawRect(m_renderer,&m_clothRect);

    if(m_nodes.size() <=0)
        return;

    for(Node& n : m_nodes) {
        const SDL_Color color = n.GetColor();
        SDL_SetRenderDrawColor(m_renderer,color.r,color.g,color.b,color.a);
        SDL_RenderFillRect(m_renderer,&n.GetRect());
    }
}