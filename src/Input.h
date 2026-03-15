#pragma once
#include <SDL_events.h>
#include "Comp.h"

class Input
{
public:
    void HandleEvent(const SDL_Event&);
    inline const IVec2& GetMousePos(){return m_mousePos;}

private:
    IVec2 m_mousePos;
};