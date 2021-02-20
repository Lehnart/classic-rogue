#include "hero.h"

#include "block.h"

#define CHARACTER_BMP_PATH "res/characters.bmp"

Hero::Hero(unsigned int x, unsigned int y, Renderer& renderer)
{
    mRect.x = x*BLOCK_WIDTH;
    mRect.y = y*BLOCK_HEIGHT;
    mRect.w = BLOCK_WIDTH;
    mRect.h = BLOCK_HEIGHT;

    SDL_Surface* heroSurface = SDL_LoadBMP(CHARACTER_BMP_PATH);
    mTexture = SDL_CreateTextureFromSurface(renderer.get(), heroSurface);
    SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(heroSurface);
}

void Hero::draw(Renderer& renderer) const{

    SDL_Rect src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = BLOCK_WIDTH;
    src_rect.h = BLOCK_HEIGHT;

    renderer.copy(mTexture, src_rect, mRect);
}
