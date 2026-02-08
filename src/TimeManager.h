#pragma once
#include <SDL.h>

class TimeManager
{
public:
    static TimeManager& GetInstance(){
        static TimeManager instance;
        return instance;
    }

    const double GetFPS() { return fps;}
    const float GetDeltaTime() { return deltaTime;}
    const float GetTotalTime() {return totalTime;}

    void Tick() {
        Uint64 currentTick = SDL_GetPerformanceCounter();
        Uint64 freq = SDL_GetPerformanceFrequency();
        deltaTime = (double)(currentTick - lastTick) / (double)freq;
        lastTick = currentTick;

        totalTime += deltaTime;

        frameCount++;
        fpsTimer += deltaTime;
        if(fpsTimer >= 1.0f)
        {
            fps = frameCount/fpsTimer;
            frameCount = 0;
            fpsTimer = 0;
        }

    }

private:
        TimeManager() {
            lastTick = SDL_GetPerformanceCounter();
        }

        TimeManager& operator=(TimeManager&&) = delete;
        TimeManager(TimeManager&&) = delete;
        TimeManager(const TimeManager&) = delete;
        TimeManager& operator=(const TimeManager&) = delete;
    
    private:
        float deltaTime = 0.0f;
        float totalTime = 0.0f;
        Uint64 lastTick = 0;
        Uint32 frameCount = 0;
        double fpsTimer = 0;
        double fps = 0;
};