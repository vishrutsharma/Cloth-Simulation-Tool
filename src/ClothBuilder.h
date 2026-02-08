#pragma once
#include "Cloth.h"
#include <SDL.h>

class ClothBuilder
{
    public:
    ~ClothBuilder() = default;
    virtual ClothBuilder& SetRenderer(SDL_Renderer*) = 0;
    virtual ClothBuilder& SetPostition(Vec2) = 0;
    virtual ClothBuilder& SetSize(int,int) = 0;
    virtual ClothBuilder& SetResolution(int,int) = 0;
    virtual ClothBuilder& SetNodeSize(int) = 0;
    virtual Cloth* Build();
};

class BasicClothBuilder : public ClothBuilder
{
    private:
        Cloth* cloth;

  public:
        BasicClothBuilder() : cloth(new Cloth()) {}
        ~BasicClothBuilder();
        
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

        ClothBuilder& SetResolution(int resX,int resY) override {
            cloth->SetResolution(resX,resY);
            return *this;
        }

        ClothBuilder& SetNodeSize(int size) override {
            cloth->SetNodeSize(size);
            return *this;
        }

        Cloth* Build() override {
            Cloth* t_cloth = cloth;
            cloth = nullptr;
            return t_cloth;
        }

}