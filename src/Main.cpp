#include <SDL.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include "Cloth.h"
#include "TimeManager.h"
#include "Node.h"
#include "ClothBuilder.h"
#include "Input.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;
constexpr float FIXED_DT = 1.0f / 60.0f;


int main(int argc,char* argv[]) {
    SDL_Window* window          = nullptr;
    SDL_Renderer* renderer      = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("My Window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if(window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    Input input{};
    Cloth* cloth = BasicClothBuilder()
                    .SetRenderer(renderer)
                    .SetSize(500,400)
                    .SetNodeSize(10)
                    .SetGap(10)
                    .SetPosition(FVec2{WINDOW_WIDTH/2,WINDOW_HEIGHT/2})
                    .SetPhysicsAttribs(Vec2{0.0f,981.0f},0.01f,0.01f)
                    .Build();

    SDL_Event e;
    bool quit = false;
    SDL_SetRenderDrawColor(renderer, 0, 0,0, 255);
    SDL_RenderClear(renderer);
    float accumulator = 0.0f;
    while (!quit) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT) quit = true;
            input.HandleEvent(e);
        }

        TimeManager::GetInstance().Tick();
        float dt = TimeManager::GetInstance().GetDeltaTime();
        accumulator += dt;
        
        while(accumulator > FIXED_DT)
        {
            cloth->Update(FIXED_DT);
            accumulator -= dt;
            cloth->ProcessInput(input);
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0,0, 255);
        SDL_RenderClear(renderer);
        cloth->Render();
        SDL_RenderPresent(renderer); 
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}