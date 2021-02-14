#include "hero.h"

#include "block.h"

Hero::Hero(unsigned int x, unsigned int y)
{
    mRect.x = x*BLOCK_WIDTH;
    mRect.y = y*BLOCK_HEIGHT;
    mRect.w = BLOCK_WIDTH;
    mRect.h = BLOCK_HEIGHT;
}

void Hero::draw(Renderer& renderer) const{
    renderer.fillRect(mRect, RED);
}
