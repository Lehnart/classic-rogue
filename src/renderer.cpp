#include "renderer.h"

#include <iostream>

#include "SDL2/SDL.h"
#include "window.h"

Renderer::Renderer(Window& window)
{
    mRendererPtr = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED);
    if (mRendererPtr == NULL){
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
    }
    if(0!=SDL_SetRenderDrawBlendMode(mRendererPtr, SDL_BLENDMODE_BLEND)){
        std::cerr << "Could not create window:" << SDL_GetError() << std::endl;
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(mRendererPtr);
}

void  Renderer::clear(){
    int sdl_error = 0;

    sdl_error = SDL_SetRenderDrawColor(mRendererPtr, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    if(sdl_error==0) sdl_error = SDL_RenderClear(mRendererPtr);

    if(sdl_error!=0){
        std::cerr << "Error during clearing " << SDL_GetError() << std::endl;
    }

}

void Renderer::copy(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_Rect& destRect){

    if (0 != SDL_RenderCopy(mRendererPtr, texture, &srcRect, &destRect) ){
        std::cerr << "Error during copy " << SDL_GetError() << std::endl;
    }
}

void Renderer::present(){
    SDL_RenderPresent(mRendererPtr);
}

void Renderer::drawRect(const SDL_Rect& rect, const SDL_Color& color){
    int sdl_error = 0;
    if(sdl_error==0) sdl_error = SDL_SetRenderDrawColor(mRendererPtr, color.r, color.g, color.b, color.a);
    if(sdl_error==0) sdl_error = SDL_RenderDrawRect(mRendererPtr, &rect);
    if(sdl_error!=0){
        std::cerr << "Error during drawRect " << SDL_GetError() << std::endl;
    }
}

void Renderer::fillRect(const SDL_Rect& rect, const SDL_Color& color){
    int sdl_error = 0;
    if(sdl_error==0) sdl_error = SDL_SetRenderDrawColor(mRendererPtr, color.r, color.g, color.b, color.a);
    if(sdl_error==0) sdl_error = SDL_RenderFillRect(mRendererPtr, &rect);
    if(sdl_error!=0){
        std::cerr << "Error during fillRect " << SDL_GetError() << std::endl;
    }
}
