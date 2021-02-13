#include <iostream>

#include "SDL2/SDL.h"

#include "block.h"
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

    bool is_running = true;
    Uint32 t= SDL_GetTicks();
    while(is_running){
        Uint32 new_t = SDL_GetTicks();
        float dt = (float)(new_t - t)/1000.f;
        t=new_t;

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                is_running = false;
            }
        }

        renderer.clear();

        for(int i=0;i<WINDOW_WIDTH/BLOCK_WIDTH;i++){
            for(int j=0;j<WINDOW_HEIGHT/BLOCK_HEIGHT;j++){
                Block b(i*BLOCK_WIDTH, j*BLOCK_HEIGHT);
                b.draw(renderer);
            }
        }


        renderer.present();
    }


    SDL_Quit();
    return 0;
}
