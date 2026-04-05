#include "Cloth.h"
#include "Comp.h"
#include <cmath>
#include <algorithm>
#include "Utils.h"
#include <iostream>

Cloth :: Cloth() {
  
    m_SimulationTimeTick = 0;
    m_inRangeNodeColor = Utils::Color::HexToSDLColor(ColorPreset::BLUE);
    m_defaultNodeColor = Utils::Color::HexToSDLColor(ColorPreset::WHITE);
    m_detectionRadius = 20;
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
            FVec2 pos {xPos,yPos};
            //SDL_Color color {Utils::Color::GetRandomColorHSV()} ;
            bool isPinned = y == 0 ;
           //isPinned  = false;
            SDL_Color color { isPinned ? Utils::Color::HexToSDLColor(ColorPreset::RED) : m_defaultNodeColor};
            Node node{pos,color,m_nodeSize,isPinned};
            m_nodes.push_back(node);
        }
    } 
    
    int hrThreadsCount = (resX - 1) * resY;
    int vrThreadsCount = (resY - 1) * resX;

    auto AddThread = [&](int indexA,int indexB)
    {
        Node& nodeA = m_nodes[indexA];
        Node& nodeB = m_nodes[indexB];
        float distance = Utils::Math::GetDistance(nodeA.m_currentPos,nodeB.m_currentPos);
        m_threads.emplace_back(indexA,indexB,distance);
    };

    for(int i = 0 ; i < m_nodes.size(); i++)
    {
        int nodeHScan = i % resX;
        int nodeVScan = i / resX;
        
        //HORIZONTAL
        if(nodeHScan != resX - 1)
            AddThread(i,i+1);
        
        //VERTICAL
        if(nodeVScan  != resY -1)
            AddThread(i,i+resX);
        
         //RIGHT DIAGONAL   
        if(nodeHScan != resX - 1 && nodeVScan != resY-1)
            AddThread(i,i+resX+1);
    
        //LEFT DIAGONAL
        if(nodeHScan != 0 && nodeVScan != resY-1)
            AddThread(i,i+resX-1);

    }
}

void Cloth::KeepInRange(Node& node)
{
    if(node.m_currentPos.y >= 800)
    {
        node.m_currentPos.y = 800;
        node.m_prevPos.y = 800;
    }
}

void Cloth::Update(float dt)
{
    if (m_nodes.empty())
        return;

    FVec2 acceleration{0.0f, m_physicsParam.m_gravity.y};
    for (int i =0; i < m_nodes.size(); i++)
    {
        Node& node = m_nodes[i];
         if (!node.IsPinned())
        {
            FVec2 velocity = node.m_currentPos - node.m_prevPos;
            velocity *= (1.0f - m_physicsParam.m_drag);
            FVec2 prevPos = node.m_currentPos;
            node.m_currentPos = node.m_currentPos + velocity + acceleration * dt * dt;
            node.m_prevPos = prevPos;
        }
        node.Update(dt);
    }

    int simulationSteps = 5;
    for(int i = 0; i < simulationSteps; i++)
    {
        AddConstraint();

        for(Node& node : m_nodes)
            KeepInRange(node);
    } 
    
}


//TODO: Optimise this by creating quadtrees
void Cloth::ProcessInput(Input& input)
{
    FVec2 mousePos = FVec2{(float)input.GetMousePos().x,(float)input.GetMousePos().y};


    for (int i = 0; i < m_threads.size(); )
    {
        Thread& thread = m_threads[i];

        const Node& a = m_nodes[thread.GetIndexA()];
        const Node& b = m_nodes[thread.GetIndexB()];

        FVec2 mid = (a.m_currentPos + b.m_currentPos) * 0.5f;
        int dist = Utils::Math::GetSQUAREDDistance(mousePos, mid);

        if (input.IsMouseButtonDown(MouseButtonType::RIGHT_BUTTON) && dist <= m_detectionRadius*2.5f )
        {
            m_threads.erase(m_threads.begin() + i);
        }
        else
        {
            i++;
        }
    }       

    for(Node& node : m_nodes)
    {
        if(node.IsPinned()) continue;

        int dist  = static_cast<int>(Utils::Math::GetSQUAREDDistance(mousePos,node.m_currentPos));
        if(dist <= m_detectionRadius*m_detectionRadius)
        {
            node.Select();
            node.SetColor(m_inRangeNodeColor);
        }
        else
        {
            node.Deselect();
            node.SetColor(m_defaultNodeColor);
        }

        if(input.IsMouseButtonDown(MouseButtonType::LEFT_BUTTON) && node.IsSelected())
        {
            // Snap to mouse logic
           node.m_currentPos = mousePos;
           node.m_prevPos = mousePos;
           node.Update(0.0);
        }
    }

}

void Cloth::AddConstraint()
{
    for(int i = 0; i < m_threads.size(); i++)
    {
        Thread& thread = m_threads[i];

        int nodeAIndex = thread.GetIndexA();
        int nodeBIndex = thread.GetIndexB();

        Node& nodeA = m_nodes[nodeAIndex];
        Node& nodeB = m_nodes[nodeBIndex];

        FVec2 diff = Utils::Math::GetDifference(nodeA.m_currentPos, nodeB.m_currentPos);

        float length = Utils::Math::GetLength(diff);
        if(length < 0.0001f)
            continue;

        float restLength = thread.GetLength();
        float stiffness = m_physicsParam.m_elasticity;
        float difference = (length - restLength) / length;
        difference *= stiffness;

        FVec2 offset = diff * difference;
        bool aPinned = nodeA.IsPinned();
        bool bPinned = nodeB.IsPinned();

        float tearThreshold = 1.5f; // tweak this (1.2–2.0)


        if(!aPinned && !bPinned)
        {
            nodeA.m_currentPos.x += offset.x * 0.5f;
            nodeA.m_currentPos.y += offset.y * 0.5f;

            nodeB.m_currentPos.x -= offset.x * 0.5f;
            nodeB.m_currentPos.y -= offset.y * 0.5f;
        }
        else if(!aPinned)
        {
            nodeA.m_currentPos.x += offset.x;
            nodeA.m_currentPos.y += offset.y;
        }
        else if(!bPinned)
        {
            nodeB.m_currentPos.x -= offset.x;
            nodeB.m_currentPos.y -= offset.y;
        }
    }
}

void Cloth :: Render() 
{
    if(!m_renderer)
        return;

    // SDL_SetRenderDrawColor(m_renderer,245,122,24,255);
    // SDL_RenderDrawRect(m_renderer,&m_clothRect);
    
    for(Node& n : m_nodes) {
        n.Render(m_renderer);
    }

    for(Thread& t : m_threads)
    {
       t.Render(m_renderer,m_nodes[t.GetIndexA()].m_currentPos,m_nodes[t.GetIndexB()].m_currentPos);
    }
}