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
        {
            if (event.button.button == SDL_BUTTON_LEFT)
                m_isMouseLeftButtonDown = true;

            if (event.button.button == SDL_BUTTON_RIGHT)
                m_isMouseRightButtonDown = true;

            SDL_GetMouseState(&m_mousePrevPos.x, &m_mousePrevPos.y);
        }
        break;

        case SDL_MOUSEBUTTONUP:
        {
            if (event.button.button == SDL_BUTTON_LEFT)
                m_isMouseLeftButtonDown = false;

            if (event.button.button == SDL_BUTTON_RIGHT)
                m_isMouseRightButtonDown = false;
        }
        break;
    }
}


    // convert this to bitmask logic
    bool Input::IsMouseButtonDown(MouseButtonType type)
    {
        switch (type)
        {
            case MouseButtonType::LEFT_BUTTON:
                return m_isMouseLeftButtonDown;
                break;

            case MouseButtonType::RIGHT_BUTTON:
                return m_isMouseRightButtonDown;
                break;
        }   
        return false; 
    }