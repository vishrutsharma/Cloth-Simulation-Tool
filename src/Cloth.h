#pragma once
#include "Node.h"
#include "Thread.h"
#include <SDL.h>
#include "Input.h"

#include <vector>

constexpr float NODE_SIZE = 1.0f; 
constexpr float FORCE = 0.5f;

class Cloth
{
    struct ClothPhysicsAttribs
    {
        FVec2 m_gravity;
        float m_drag;
        float m_elasticity;
    };

private:
    std::vector<Node> m_nodes;
    std::vector<Thread> m_threads;
    SDL_Renderer* m_renderer;
    ClothPhysicsAttribs m_physicsParam;
    float m_SimulationTimeTick;
    FVec2 m_position;
    int m_clothWidth;
    int m_clothHeight;
    int m_nodeSize;
    int m_nodesGap;
    SDL_Rect m_clothRect;

    SDL_Color m_inRangeColor;
    SDL_Color m_offRangeColor;
    int m_detectionRadius;
    
private:
    void KeepInRange(Node&);
    void AddThread(int,int);
    void AddConstraint();

public:
    Cloth();
    inline void SetRenderer(SDL_Renderer* renderer) {m_renderer = renderer;}
    inline void SetPosition(FVec2 pos) {m_position = pos;}
    inline void SetSize(int width,int height) { m_clothWidth = width; m_clothHeight = height;}
    inline void SetNodeSize(int nodeSize) {m_nodeSize = nodeSize;}
    inline void SetGap(int gap) {m_nodesGap = gap;}
    inline void SetPhysicsAttribs(FVec2 gravity, float drag,float elasticity) { m_physicsParam ={gravity,drag,elasticity};}
    
    void ProcessInput(Input&);
    void Build();
    void Update(float);
    void Render();
};