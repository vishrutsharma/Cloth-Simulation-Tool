#pragma once
#include <SDL_events.h>
#include "Comp.h"

class Input
{
public:
    void HandleEvent(const SDL_Event&);
    inline const IVec2& GetMousePos(){return m_mousePos;}
    inline const IVec2& GetMousePrevPos() {return m_mousePrevPos;}
    bool IsMouseButtonDown() {return m_isMouseButtonDown;}

private:
    IVec2 m_mousePos;
    IVec2 m_mousePrevPos{0,0};
    bool m_isMouseButtonDown = false;
};