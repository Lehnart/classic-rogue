#ifndef HERO_H
#define HERO_H

#include "SDL2/SDL.h"

#include "block.h"
#include "renderer.h"

class Hero
{
public:
    Hero(unsigned int x, unsigned int y, Renderer& renderer);

    void draw(Renderer& renderer) const;

    int& getX(){return mRect.x;};
    int& getY(){return mRect.y;};

    int getBlockX(){return mRect.x/BLOCK_WIDTH;};
    int getBlockY(){return mRect.y/BLOCK_HEIGHT;};

private:
    SDL_Rect mRect;
    SDL_Texture* mTexture;
};

#endif // HERO_H
