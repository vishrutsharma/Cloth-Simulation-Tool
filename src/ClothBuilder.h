#pragma once
#include "Cloth.h"
#include <SDL.h>
#include <memory>

class ClothBuilder
{
    public:
    ~ClothBuilder() = default;
    virtual ClothBuilder& SetRenderer(SDL_Renderer*) = 0;
    virtual ClothBuilder& SetPosition(Vec2) = 0;
    virtual ClothBuilder& SetSize(int,int) = 0;
    virtual ClothBuilder& SetNodeSize(int size) = 0;
    virtual ClothBuilder& SetGap(int gap) = 0;
    virtual Cloth* Build() = 0;
};

class BasicClothBuilder : public ClothBuilder
{
    private:
        Cloth* cloth;

    public:
        BasicClothBuilder() : cloth(new Cloth()) {}
        ~BasicClothBuilder()
        {
            delete cloth;
        }
        
        ClothBuilder& SetRenderer(SDL_Renderer* renderer) override{
            cloth->SetRenderer(renderer);
            return *this;
        }

        ClothBuilder& SetPosition(Vec2 position) override{
            cloth->SetPosition(position);
            return *this;
        }

        ClothBuilder& SetSize(int width,int height) override {
            cloth->SetSize(width,height);
            return *this;
        }

        ClothBuilder& SetNodeSize(int size) override {
            cloth->SetNodeSize(size);
            return *this;
        }

        ClothBuilder& SetGap(int gap) override {
            cloth->SetGap(gap);
            return *this;
        }

        Cloth* Build() override {
            cloth->Build();
            Cloth* t_cloth = cloth;
            cloth = nullptr;
            return t_cloth;
        }
};