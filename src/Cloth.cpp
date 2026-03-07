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

    // Nodes Creation
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
    
    int hrThreadsCount = (resX - 1) * resY;
    int vrThreadsCount = (resY - 1) * resX;
    
    for(int i = 0 ; i < m_nodes.size(); i++)
    {
        Node& node = m_nodes[i];
        int nodeHScan = i % resX;
        int nodeVScan = i / resX;
        
        //HORIZONTAL
        if(nodeHScan != resX - 1)
            AddThread(node,m_nodes[i+1]);
        
        //VERTICAL
        if(nodeVScan  != resY -1)
            AddThread(node,m_nodes[i+resX]);
        
         //RIGHT DIAGONAL   
        if(nodeHScan != resX - 1 && nodeVScan != resY-1)
            AddThread(node,m_nodes[i+resX+1]);
    
        //LEFT DIAGONAL
        if(nodeHScan != 0 && nodeVScan != resY-1)
            AddThread(node,m_nodes[i+resX-1]);
    }
}

void Cloth::KeepInRange(Node& node)
{
    if(node.m_currentPos.y >= 800)  
           node.m_currentPos.y = 800;

    // Define region bounds constraints
        
}

void Cloth::Update(float dt)
{
    if (m_nodes.empty())
        return;

    Vec2 force{0.0f, FORCE};
    Vec2 acceleration { force.x / m_nodes[0].GetMass(), force.y / m_nodes[0].GetMass()};
    for (Node& node : m_nodes)
    {
        const Vec2 prevPos = node.m_currentPos;
        node.m_currentPos.x = 2.0f * node.m_currentPos.x - node.m_prevPos.x + acceleration.x * dt * dt;
        node.m_currentPos.y = 2.0f * node.m_currentPos.y - node.m_prevPos.y + acceleration.y * dt * dt;
        node.m_prevPos = prevPos;

        KeepInRange(node);
        node.Update(dt);
    }
    AddConstaint();
}

void Cloth :: Render() 
{
    if(!m_renderer)
        return;

    SDL_SetRenderDrawColor(m_renderer,245,122,24,255);
    SDL_RenderDrawRect(m_renderer,&m_clothRect);
    
    for(Node& n : m_nodes) {
        n.Render(m_renderer);
    }

    for(Thread& t : m_threads)
    {
       t.Render(m_renderer);
    }
}

void Cloth::AddConstaint()
{   


}

void Cloth::AddThread(Node& nodeA ,Node& nodeB)
{
    m_threads.emplace_back(nodeA,nodeB,Utils::Math::GetDistance(nodeA.m_currentPos,nodeB.m_currentPos));   
}