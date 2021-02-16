

#include <iostream>

#include "SDL2/SDL.h"

#include "block.h"
#include "clock.h"
#include "hero.h"
#include "renderer.h"
#include "window.h"

bool init_SDL(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur d'initialisation de la SDL : " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    if(argc >1) std::cerr << "Pas d'arguments comme " << argv[0] << std::endl;
    if( !init_SDL() ) return 1;

    Window window;
    Renderer renderer(window);

    Hero hero(20,20);
    Clock clock(600,464, renderer);

    bool is_running = true;
    while(is_running){

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                is_running = false;
            }

            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_UP){
                    hero.getY()-=BLOCK_HEIGHT;
                }
                else if(event.key.keysym.sym == SDLK_DOWN){
                    hero.getY()+=BLOCK_HEIGHT;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    hero.getX()-=BLOCK_WIDTH;
                }
                else if(event.key.keysym.sym == SDLK_RIGHT){
                    hero.getX()+=BLOCK_WIDTH;
                }
            }
        }

        renderer.clear();

        for(unsigned int i=0;i<WINDOW_WIDTH/BLOCK_WIDTH;i++){
            for(unsigned  int j=0;j<WINDOW_HEIGHT/BLOCK_HEIGHT;j++){
                Block b(i*BLOCK_WIDTH, j*BLOCK_HEIGHT);
                b.draw(renderer);
            }
        }
        hero.draw(renderer);
        clock.draw(renderer);

        renderer.present();
    }


    SDL_Quit();
    return 0;
}
