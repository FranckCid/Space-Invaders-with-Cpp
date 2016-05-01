#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include <vector>

#include "GameObject.h"
#include "Spaceship.h"

#include <SDL/SDL.h>

//Engine variables
SDL_Surface *screen=NULL;
SDL_Event event;

//Engine methods
void Load();
void Logic();
void DrawScreen();
void Quit();

//Variables
Spaceship player;
std::vector<Bullet> bullets;

int main ( int argc, char** argv )
{

    const int FPS = 30;
    Uint32 start;
    float frame=0;

    Load();

    while(1){

        start = SDL_GetTicks();

        SDL_PollEvent(&event);

        if(event.type == SDL_QUIT){
            break;
        }

        Logic();
        DrawScreen();

        frame += 0.2;
        if(frame > 10){
            frame = 0;
        }
        if(1000/FPS > SDL_GetTicks()-start){
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }

    }

    Quit();

    return 0;
}

void Load(){

    SDL_Init(SDL_INIT_EVERYTHING);

    screen = SDL_SetVideoMode(600, 500, 32, SDL_SWSURFACE);

}

void Logic(){

    const Uint8 *keystates = SDL_GetKeyState(NULL);

    if(keystates[SDLK_a]){
        player.Move(-10, 0);
    }else if(keystates[SDLK_d]){
        player.Move(10, 0);
    }

    if(keystates[SDLK_SPACE]){
        player.Shot(bullets);
    }

    for(int i=0; i<bullets.size(); i++){
        bullets[i].Move();
        if(bullets[i].rect.y < 0){
            bullets.erase(bullets.begin() + i);
        }
    }

}

void DrawScreen(){

    SDL_FillRect(screen, NULL, 0);

    SDL_FillRect(screen, &player.rect, 255);

    for(int i=0; i<bullets.size(); i++){
        SDL_FillRect(screen, &bullets[i].rect, 253);
    }

    SDL_Flip(screen);

}

void Quit(){
    SDL_Quit();
}
