#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"

#define WINDOW_X0 100
#define WINDOW_Y0 100
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Window
{
public:
    Window();
    ~Window();

    SDL_Window* get();

private:
    SDL_Window* mWindowPtr;
};

#endif // WINDOW_H
