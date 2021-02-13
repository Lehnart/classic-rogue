#include "block.h"

#include <iostream>

#include "renderer.h"
Block::Block(unsigned int x0, unsigned int y0)
{
    mRect.x = x0;
    mRect.y = y0;
    mRect.w = BLOCK_WIDTH;
    mRect.h = BLOCK_HEIGHT;

}

void Block::draw(Renderer& renderer){
    renderer.drawRect(mRect, GREY);
}
