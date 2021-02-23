#ifndef GOLDPILE_H
#define GOLDPILE_H

#define ITEM_PATH "res/items.bmp"

#include "renderer.h"

class GoldPile{

public:
    GoldPile(unsigned int x, unsigned int y);
    ~GoldPile();

    void draw(Renderer& renderer) const;

    unsigned int getX() const {return mX;}
    unsigned int getY() const {return mY;}

private :
    unsigned int mX;
    unsigned int mY;
    static SDL_Texture* mTexture;
};

#endif // CLOCK_H
