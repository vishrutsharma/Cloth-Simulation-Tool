#pragma once
#include "Node.h"

class Node;
class Thread
{
public:
    Thread(int,int,float);
    void Update(SDL_Renderer*,Vec2&,Vec2&);
    inline float GetLength() {return m_length;}
    
private :
    int m_nodeAIndex;
    int m_nodeBIndex;
    float m_length;
};