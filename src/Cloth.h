#pragma once
#include "Node.h"
#include "Thread.h"
#include <SDL.h>

#include <vector>

#define NODE_SIZE 1
#define FORCE 0.2

class Cloth
{
private:
    std::vector<Node> m_nodes;
    std::vector<Thread> m_threads;
    SDL_Renderer* m_renderer;
    float m_SimulationTimeTick;
    Vec2 m_position;
    int m_clothWidth;
    int m_clothHeight;
    int m_nodeSize;
    int m_nodesGap;
    SDL_Rect m_clothRect;
  
private:
    //void AddNode(Vec2&&);
    void KeepInRange(Node&);
    void AddThread(int,int);
    void AddConstaint();

public:
    Cloth();
    inline void SetRenderer(SDL_Renderer* renderer) {m_renderer = renderer;}
    inline void SetPosition(Vec2 pos) {m_position = pos;}
    inline void SetSize(int width,int height) { m_clothWidth = width; m_clothHeight = height;}
    inline void SetNodeSize(int nodeSize) {m_nodeSize = nodeSize;}
    inline void SetGap(int gap) {m_nodesGap = gap;}
    
    void Build();
    void Update(float);
    void Render();
};