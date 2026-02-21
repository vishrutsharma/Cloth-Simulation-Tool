#include <SDL.h>
#include <stdio.h>
#include <conio.h>
#include "Cloth.h"
#include "TimeManager.h"
#include "Node.h"
#include "ClothBuilder.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;


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

    Cloth* cloth = BasicClothBuilder()
                    .SetRenderer(renderer)
                    .SetSize(500,80)
                    .SetNodeSize(10)
                    .SetGap(10)
                    .SetPosition(Vec2{WINDOW_WIDTH/2,WINDOW_HEIGHT/2})
                    .Build();

    
    SDL_Event e;
    bool quit = false;
    SDL_SetRenderDrawColor(renderer, 0, 0,0, 255);
    SDL_RenderClear(renderer);
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
    
        }
        SDL_SetRenderDrawColor(renderer, 0, 0,0, 255);
        SDL_RenderClear(renderer);
        TimeManager::GetInstance().Tick();
        //cloth->Update(TimeManager::GetInstance().GetDeltaTime());
        cloth->Render();
        SDL_RenderPresent(renderer); 
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}