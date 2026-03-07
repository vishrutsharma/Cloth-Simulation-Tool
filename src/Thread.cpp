#include "Thread.h"

Thread::Thread(int nodeAIndex,int nodeBIndex,float length) :
                                    m_nodeAIndex(nodeAIndex) , m_nodeBIndex(nodeBIndex), m_length(length) {} 



void Thread::Update(SDL_Renderer* renderer,Vec2& nodeAPos,Vec2& nodeBPos)
{
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
    int x1 = static_cast<int>(nodeAPos.x);
    int y1 = static_cast<int>(nodeAPos.y);
    int x2 = static_cast<int>(nodeBPos.x);
    int y2 = static_cast<int>(nodeBPos.y);
    
    SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
}
