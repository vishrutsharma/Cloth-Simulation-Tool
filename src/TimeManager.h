#pragma once
#include <SDL.h>

class TimeManager
{
public:
    static TimeManager& GetInstance(){
        static TimeManager instance;
        return instance;
    }

    void Tick() {
        Uint64 currentTick = SDL_GetTicks(); 
        deltaTime = (currentTick - lastTick) * 0.01f;
        lastTick = currentTick;
        totalTime += deltaTime;
    }

    const float GetDeltaTime() {
        return deltaTime;
    }

    const float GetTotalTime() {
        return totalTime;
    }

private:
        TimeManager() {
            lastTick = SDL_GetTicks();
        }

        TimeManager& operator=(TimeManager&&) = delete;
        TimeManager(TimeManager&&) = delete;
        TimeManager(const TimeManager&) = delete;
        TimeManager& operator=(const TimeManager&) = delete;
    
    private:
        float deltaTime = 0.0f;
        float totalTime = 0.0f;
        Uint32 lastTick = 0;
};