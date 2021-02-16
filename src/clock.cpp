#include "clock.h"

#include "block.h"
#include "renderer.h"

#include <ctime>

#include "SDL2/SDL.h"

Clock::Clock(unsigned int x, unsigned int y, Renderer& renderer):
    mX(x),
    mY(y)
{
    SDL_Surface* fontSurface = SDL_LoadBMP(FONT_PATH);
    mFontTexture = SDL_CreateTextureFromSurface(renderer.get(), fontSurface);
    SDL_SetTextureBlendMode(mFontTexture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(fontSurface);
}

void Clock::draw(Renderer& renderer) const{

    SDL_Rect src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = BLOCK_WIDTH;
    src_rect.h = BLOCK_HEIGHT;


    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    int hour = now->tm_hour;
    int minute = now->tm_min;

    for(int i = 0; i<5; i++){
        SDL_Rect dest_rect;
        dest_rect.x = mX + (i*BLOCK_WIDTH);
        dest_rect.y = mY;
        dest_rect.w = BLOCK_WIDTH;
        dest_rect.h = BLOCK_HEIGHT;
        renderer.fillRect(dest_rect, GREY);

        char digit;
        if      (i==0) digit = hour/10;
        else if (i==1) digit = hour%10;
        else if (i==2) digit = 10;
        else if (i==3) digit = minute/10;
        else           digit = minute%10;
        if ( digit >= 0 && digit <= 10 ) {
            src_rect.x = BLOCK_WIDTH*digit;
            renderer.copy(mFontTexture, src_rect, dest_rect);
        }
    }
}
