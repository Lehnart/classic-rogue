#ifndef BLOCK_H
#define BLOCK_H

#define BLOCK_WIDTH 8
#define BLOCK_HEIGHT 16

#include "renderer.h"

class Block
{
public:
    Block(unsigned int x0, unsigned int y0);

    void draw(Renderer& renderer);

private:

    SDL_Rect mRect;

};

#endif // BLOCK_H
