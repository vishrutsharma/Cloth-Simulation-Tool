#include "Cloth.h"
#include "TimeManager.h"

Cloth::Cloth(SDL_Renderer* renderer) : m_renderer(renderer) {}

void Cloth::AddNode(IVec2&& desiredPos) {
    IVec2 pos {desiredPos.x,desiredPos.y};
    SDL_Color color {255,255,255,255};
    Node node{pos,color};
    m_nodes.push_back(node);
}

void Cloth::Update() {
    if(m_nodes.size() >0)
        return;
    
    if(m_SimulationTimeTick <= 10)
    {
        // currently the mass is same for all nodes
        // later it will vary based on user input
        IVec2 acceleration {FORCE / m_nodes[0].GetMass()};

        float deltaTime = TimeManager::GetInstance().GetDeltaTime();
        for(Node& node : m_nodes){
            node.m_velocity += acceleration * deltaTime;
            node.m_currentPos += node.m_velocity * deltaTime;
            m_SimulationTimeTick += deltaTime;
            node.Update();
        }
        SDL_Delay(2000);
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