#include "block.h"

#include <iostream>

#include "renderer.h"

SDL_Texture* Block::mTexture = nullptr;

Block::Block():
    Block(0,0,BlockType::none){}


Block::Block(unsigned int x0, unsigned int y0, BlockType blockType):
    mIsVisible(false),
    mType(blockType)
{
    mRect.x = x0;
    mRect.y = y0;
    mRect.w = BLOCK_WIDTH;
    mRect.h = BLOCK_HEIGHT;
}

Block::~Block(){
    if(mTexture == nullptr){
        SDL_DestroyTexture(mTexture);
    }
}

bool Block::isWalkable() const{
    return ( mType == ground ||
            mType == vdoor ||
            mType == hdoor ||
            mType == corridor );
}

void Block::draw(Renderer& renderer){

    if(!mIsVisible){
        return;
    }

    if(mTexture == nullptr){
        SDL_Surface* blockSurface = SDL_LoadBMP(BLOCK_BMP_PATH);
        mTexture = SDL_CreateTextureFromSurface(renderer.get(), blockSurface);
        SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
        SDL_FreeSurface(blockSurface);
    }

    SDL_Rect src_rect;
    src_rect.x = int(mType) * BLOCK_WIDTH;
    src_rect.y = 0;
    src_rect.w = BLOCK_WIDTH;
    src_rect.h = BLOCK_HEIGHT;

    renderer.copy(mTexture, src_rect, mRect);
}
