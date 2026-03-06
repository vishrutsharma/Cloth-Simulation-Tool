#pragma once
#include "Node.h"

class Node;
class Thread
{
public:
    Thread(Node&,Node&,int);
    void Render(SDL_Renderer*);
    void Update(float dt);
    
private :
    Node& m_nodeA;
    Node& m_nodeB;
    int m_length;
};