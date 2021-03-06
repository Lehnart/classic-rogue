#include <iostream>

#include "SDL2/SDL.h"

#include "block.h"
#include "clock.h"
#include "dungeon.h"
#include "goldpile.h"
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

    Dungeon dungeon(80,30);

    int x,y;
    dungeon.getRandomRoomPosition(x,y);
    Hero hero(x,y, renderer);


    Clock clock(600,464, renderer);

    bool is_running = true;
    while(is_running){

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                is_running = false;
            }

            if(event.type == SDL_KEYDOWN){
                int bx = hero.getBlockX();
                int by = hero.getBlockY();

                if(event.key.keysym.sym == SDLK_UP){
                    Block& b = dungeon.block(bx,by-1);
                    if(b.isWalkable()) hero.getY()-=BLOCK_HEIGHT;
                }
                else if(event.key.keysym.sym == SDLK_DOWN){
                    Block& b = dungeon.block(bx,by+1);
                    if(b.isWalkable())hero.getY()+=BLOCK_HEIGHT;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    Block& b = dungeon.block(bx-1,by);
                    if(b.isWalkable())hero.getX()-=BLOCK_WIDTH;
                }
                else if(event.key.keysym.sym == SDLK_RIGHT){
                    Block& b = dungeon.block(bx+1,by);
                    if(b.isWalkable())hero.getX()+=BLOCK_WIDTH;
                }
            }
        }

        dungeon.view(hero.getBlockX(),hero.getBlockY());

        renderer.clear();

        dungeon.draw(renderer);
        hero.draw(renderer);
        clock.draw(renderer);

        renderer.present();
    }


    SDL_Quit();
    return 0;
}
