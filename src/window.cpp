#include "window.h"

#include <iostream>

Window::Window()
{
    mWindowPtr = SDL_CreateWindow(
        "cpp-old-rogue",
        WINDOW_X0,
        WINDOW_Y0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL
        );

    if (mWindowPtr == NULL){
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
    }
}


Window::~Window()
{
    SDL_DestroyWindow(mWindowPtr);
}

SDL_Window* Window::get(){
    return mWindowPtr;
}
