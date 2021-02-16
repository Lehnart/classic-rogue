#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_WIDTH 5
#define FONT_PATH "res/font.bmp"

#include "renderer.h"

class Clock{

public:
    Clock(unsigned int x, unsigned int y, Renderer& renderer);

    void draw(Renderer& renderer) const;

private :
    unsigned int mX;
    unsigned int mY;
    SDL_Texture* mFontTexture;
};

#endif // CLOCK_H
