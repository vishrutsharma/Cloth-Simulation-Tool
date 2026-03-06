#include "Thread.h"

Thread::Thread(Node& nodeA,Node& nodeB,int length) :
                                    m_nodeA(nodeA) , m_nodeB(nodeB), m_length(length) {} 

void Thread::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
    int x1 = static_cast<int>(m_nodeA.m_currentPos.x);
    int y1 = static_cast<int>(m_nodeA.m_currentPos.y);
    int x2 = static_cast<int>(m_nodeB.m_currentPos.x);
    int y2 = static_cast<int>(m_nodeB.m_currentPos.y);
    
    SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
}

void Thread::Update(float dt)
{
}