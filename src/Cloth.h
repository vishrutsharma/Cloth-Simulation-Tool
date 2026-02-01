#pragma once
#include "Node.h"
#include <SDL_render.h>

#include <vector>

#define NODE_SIZE 1
#define FORCE 2

class Cloth
{
private:
    std::vector<Node> m_nodes;
    SDL_Renderer* m_renderer;
public:
    Cloth(SDL_Renderer*);
    void AddNode(IVec2&&);
    void Update();
    void Render();
    inline const Node& GetNodeInfo(int index) {return m_nodes.at(index);}

};