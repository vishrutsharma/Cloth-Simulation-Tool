#pragma once
#include <SDL_events.h>
#include "Comp.h"

enum MouseButtonType
{
    LEFT_BUTTON,
    RIGHT_BUTTON
};

class Input
{
public:
    void HandleEvent(const SDL_Event&);
    inline const IVec2& GetMousePos(){return m_mousePos;}
    inline const IVec2& GetMousePrevPos() {return m_mousePrevPos;}
    bool IsMouseButtonDown(MouseButtonType);

private:
    IVec2 m_mousePos;
    IVec2 m_mousePrevPos{0,0};
    bool m_isMouseLeftButtonDown = false;
    bool m_isMouseRightButtonDown = false;

};