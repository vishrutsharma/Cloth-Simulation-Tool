#include "Cloth.h"

Cloth::Cloth(SDL_Renderer* renderer) : m_renderer(renderer) {}

void Cloth::AddNode(IVec2&& desiredPos)
{
    IVec2 pos {desiredPos.x,desiredPos.y};
    SDL_Color color {255,255,255,255};
    Node node{pos,color};
    m_nodes.push_back(std::move(node));
}

void Cloth::Render()
{
    if(!m_renderer)
        return;

    if(m_nodes.size() <=0)
        return;

    for(Node& n : m_nodes)
    {
        const SDL_Color color = n.GetColor();
        SDL_SetRenderDrawColor(m_renderer,color.r,color.g,color.b,color.a);
        SDL_RenderFillRect(m_renderer,&n.GetRect());
    }
}

void Cloth::Update()
{
    if(m_nodes.size() <=0)
        return;

    
}