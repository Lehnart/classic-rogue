#ifndef HERO_H
#define HERO_H

#include "SDL2/SDL.h"

#include "renderer.h"

class Hero
{
public:
    Hero(unsigned int x, unsigned int y, Renderer& renderer);

    void draw(Renderer& renderer) const;

    int& getX(){return mRect.x;};
    int& getY(){return mRect.y;};

private:
    SDL_Rect mRect;
    SDL_Texture* mTexture;
};

#endif // HERO_H
