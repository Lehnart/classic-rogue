#ifndef RENDERER_H
#define RENDERER_H

#include "window.h"

static SDL_Color BLACK       =  {0  ,   0,   0, 255};
static SDL_Color GREY_DARK   =  {192, 192, 192, 255};
static SDL_Color GREY        =  {128, 128, 128, 255};
static SDL_Color GREY_LIGHT  =  { 64,  64,  64, 255};
static SDL_Color RED         =  {255,   0,   0, 255};
static SDL_Color BROWN       =  {201, 150,  30, 255};

class Renderer
{
public:
    Renderer(Window& window);
    ~Renderer();

    void clear();
    void copy(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_Rect& destRect);
    void present();
    void drawRect(const SDL_Rect& rect, const SDL_Color& color = BLACK);
    void Renderer::fillRect(const SDL_Rect& rect, const SDL_Color& color = BLACK);

    SDL_Renderer* get(){return mRendererPtr;}
private:
    SDL_Renderer* mRendererPtr;
};

#endif // RENDERER_H
