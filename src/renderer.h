#ifndef RENDERER_H
#define RENDERER_H

#include "window.h"

static SDL_Color BLACK = {0,0,0,255};
static SDL_Color GREY =  {128,128,128,255};
class Renderer
{
public:
    Renderer(Window& window);
    ~Renderer();

    void clear();
    void present();
    void drawRect(const SDL_Rect& rect, const SDL_Color& color = BLACK);

private:
    SDL_Renderer* mRendererPtr;
};

#endif // RENDERER_H
