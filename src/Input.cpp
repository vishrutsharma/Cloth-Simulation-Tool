#include "Input.h"
#include <iostream>

void Input::HandleEvent(const SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_MOUSEMOTION:
        {
            SDL_GetMouseState(&m_mousePos.x,&m_mousePos.y);
            IVec2 delta = m_mousePos - m_mousePrevPos;
            m_mousePrevPos = m_mousePos;
        }
        break;

        case SDL_MOUSEBUTTONDOWN:
        m_isMouseButtonDown = true;
        SDL_GetMouseState(&m_mousePrevPos.x,&m_mousePrevPos.y); 
        break;

        case SDL_MOUSEBUTTONUP:
        m_mousePrevPos = {0,0};
        m_isMouseButtonDown = false;
        break;
    }
}