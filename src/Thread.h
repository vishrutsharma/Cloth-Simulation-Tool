#pragma once
#include "Node.h"

class Node;
class Thread
{
public:
    Thread(int,int,float);
    void Render(SDL_Renderer*,Vec2&,Vec2&);
    inline float GetLength() {return m_length;}
    inline int GetIndexA() {return m_nodeAIndex;}
    inline int GetIndexB() {return m_nodeBIndex;}
    
private :
    int m_nodeAIndex;
    int m_nodeBIndex;
    float m_length;
};