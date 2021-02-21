#ifndef BLOCK_H
#define BLOCK_H

#define BLOCK_WIDTH 8
#define BLOCK_HEIGHT 16
#define BLOCK_BMP_PATH "res/block.bmp"
#include "renderer.h"

enum BlockType{
    ground = 0,
    vwall = 1,
    hwall = 2,
    ulwall = 3,
    urwall = 4,
    dlwall = 5,
    drwall = 6,
    vdoor = 7,
    hdoor = 8,
    corridor = 9,
    none
};

class Block
{
public:
    Block();
    Block(unsigned int x0, unsigned int y0, BlockType type);
    ~Block();

    void draw(Renderer& renderer);

    BlockType getType() const {return mType;}

    void setX(int x){ mRect.x = x;}
    void setY(int y){ mRect.y = y;}
    void setType(BlockType type){ mType = type;}
    void setVisible(){ mIsVisible = true; }

    bool isWalkable() const;

private:

    bool mIsVisible;

    SDL_Rect mRect;
    BlockType mType;

    static SDL_Texture* mTexture;
};

#endif // BLOCK_H
