#pragma once
#include "Comp.h"
#include <SDL_rect.h>
#include <SDL_render.h>

class Node
{
private:
    float m_mass;
    SDL_Rect m_rect;
    SDL_Color m_color;
    int m_size;

    bool m_isPinned;
    bool m_isSelected;

public:

    Node(FVec2&, SDL_Color&, int size, bool);

    inline const SDL_Color& GetColor() const { return m_color; }
    inline const SDL_Rect& GetRect() const { return m_rect; }
    inline float GetMass() const { return m_mass; }

    inline bool IsPinned() const { return m_isPinned; }

    inline void Pin() { m_isPinned = true; }
    inline void Unpin() { m_isPinned = false; }

    inline void Select() { m_isSelected = true; }
    inline void Deselect() { m_isSelected = false; }

    void Render(SDL_Renderer*);
    void Update(float dt);
    void SetPos(FVec2& pos);

    FVec2 m_currentPos;
    FVec2 m_prevPos;
    FVec2 m_velocity;
};