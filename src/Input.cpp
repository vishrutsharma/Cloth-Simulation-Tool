#include "Input.h"
#include <iostream>

void Input::HandleEvent(const SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_MOUSEMOTION:
        SDL_GetMouseState(&m_mousePos.x,&m_mousePos.y);
        break;

        case SDL_MOUSEBUTTONDOWN:
        
        break;

        case SDL_MOUSEBUTTONUP:
        break;
    }
}