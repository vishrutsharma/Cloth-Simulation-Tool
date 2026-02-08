#include "Cloth.h"

Cloth::Cloth() {
    m_SimulationTimeTick = 0;
}

void Cloth::AddNode(Vec2&& desiredPos) {
    Vec2 pos {desiredPos.x,desiredPos.y};
    SDL_Color color {255,255,255,255};
    Node node{pos,color};
    m_nodes.push_back(node);
}

void Cloth::Update(float dt) {
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

void Cloth::Render() {
    if(!m_renderer)
        return;

    if(m_nodes.size() <=0)
        return;

    for(Node& n : m_nodes) {
        const SDL_Color color = n.GetColor();
        SDL_SetRenderDrawColor(m_renderer,color.r,color.g,color.b,color.a);
        SDL_RenderFillRect(m_renderer,&n.GetRect());
    }
}