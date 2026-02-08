#pragma once
#include "Node.h"
#include <SDL.h>

#include <vector>

#define NODE_SIZE 1
#define FORCE 50

class Cloth
{
private:
    std::vector<Node> m_nodes;
    SDL_Renderer* m_renderer;
    float m_SimulationTimeTick;
    Vec2 m_position;
    int m_clothWidth;
    int m_clothHeight;
    int m_resolutionX;
    int m_resolutionY;
    int m_nodeSize;

public:
    Cloth();
    inline void SetRenderer(SDL_Renderer* renderer) {m_renderer = renderer;}
    inline void SetPosition(Vec2 pos) {m_position = pos;}
    inline void SetSize(int width,int height) { m_clothWidth = width; m_clothHeight = height;}
    inline void SetResolution(int resX,int resY) {m_resolutionX = resX; m_resolutionY = resY;}
    inline void SetNodeSize(int nodeSize) {m_nodeSize = nodeSize;}
    void AddNode(Vec2&&);
    void Update(float);
    void Render();
    inline const Node& GetNodeInfo(int index) {return m_nodes.at(index);}

};