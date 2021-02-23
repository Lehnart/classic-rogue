#include "goldpile.h"

#include "block.h"

SDL_Texture* GoldPile::mTexture = nullptr;

GoldPile::GoldPile(unsigned int x, unsigned int y):
    mX(x),
    mY(y)
{}

GoldPile::~GoldPile(){
}

void GoldPile::draw(Renderer& renderer) const{

    if (mTexture == nullptr){
        SDL_Surface* surface = SDL_LoadBMP(ITEM_PATH);
        mTexture = SDL_CreateTextureFromSurface(renderer.get(), surface);
        SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
        SDL_FreeSurface(surface);
    }

    SDL_Rect src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = BLOCK_WIDTH;
    src_rect.h = BLOCK_HEIGHT;

    SDL_Rect dest_rect;
    dest_rect.x = mX*BLOCK_WIDTH;
    dest_rect.y = mY*BLOCK_HEIGHT;
    dest_rect.w = BLOCK_WIDTH;
    dest_rect.h = BLOCK_HEIGHT;
    renderer.fillRect(dest_rect, GREY);
    renderer.copy(mTexture, src_rect, dest_rect);

}
