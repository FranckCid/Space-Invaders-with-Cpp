#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include <vector>
#include <time.h>

#include "GameObject.h"
#include "Spaceship.h"
#include "Block.h"
#include "Alien.h"
#include "Bullet.h"
#include "AlienBullet.h"

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
std::vector<AlienBullet> ebullets;
std::vector<Block> blocks;
std::vector<Alien> aliens;

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

    srand(static_cast<unsigned int>(time(0)));

    SDL_Init(SDL_INIT_EVERYTHING);

    screen = SDL_SetVideoMode(600, 500, 32, SDL_SWSURFACE);

    blocks.push_back(Block());
    for(int j=0; j<5; j++){
        for(int i=0; i<11; i++){
            aliens.push_back(Alien(35*i+35, 35*j+35));
        }
    }

}

int tick=0, counter=0, dirx=1, toshoot=0;
void Logic(){

    const Uint8 *keystates = SDL_GetKeyState(NULL);

    if(keystates[SDLK_a]){
        player.Move(-10, 0);
    }else if(keystates[SDLK_d]){
        player.Move(10, 0);
    }

    if(keystates[SDLK_SPACE] && toshoot > 25){
        player.Shot(bullets);
        toshoot = 0;
    }

    for(int i=0; i<bullets.size(); i++){
        bullets[i].Move();
        for(int j=0; j<blocks.size(); j++){
            if(bullets[i].Intersects(blocks[j].rect)){
                if(blocks[j].Damage()){
                    blocks.erase(blocks.begin()+j);
                }
                bullets.erase(bullets.begin()+i);
            }
        }
        for(int j=0; j<aliens.size(); j++){
            if(bullets[i].Intersects(aliens[j].rect)){
                aliens.erase(aliens.begin()+j);
                bullets.erase(bullets.begin() + i);
            }
        }
        if(bullets[i].rect.y < 0){
            bullets.erase(bullets.begin() + i);
        }
    }

    for(int i=0; i<ebullets.size(); i++){
        ebullets[i].Move();
        for(int j=0; j<blocks.size(); j++){
            if(ebullets[i].Intersects(blocks[j].rect)){
                if(blocks[j].Damage()){
                    blocks.erase(blocks.begin()+j);
                }
                ebullets.erase(ebullets.begin()+i);
            }
        }
        if(ebullets[i].Intersects(player.rect)){
            player.Damage();
        }
        if(ebullets[i].rect.y > 500){
            ebullets.erase(ebullets.begin() + i);
        }
    }

    if(counter > 5){
        if(tick < 20){
            for(int i=0; i<aliens.size(); i++){
                aliens[i].Move(7*dirx, 0);
            }
        }else{
            for(int i=0; i<aliens.size(); i++){
                aliens[i].Move(0, 25);
            }
            dirx *= -1;
            tick = 0;
        }
        counter = 0;
        tick++;
    }

    if(rand()%800+1>788){
        aliens[rand()%aliens.size()].Shot(ebullets);
    }

    counter++;
    toshoot++;
    std::cout << ebullets.size() << "\n";

}

void DrawScreen(){

    SDL_FillRect(screen, NULL, 0);

    SDL_FillRect(screen, &player.rect, 255);

    for(int i=0; i<bullets.size(); i++){
        SDL_FillRect(screen, &bullets[i].rect, 253);
    }

    for(int i=0; i<ebullets.size(); i++){
        SDL_FillRect(screen, &ebullets[i].rect, 253);
    }

    for(int i=0; i<blocks.size(); i++){
        SDL_FillRect(screen, &blocks[i].rect, 0x0000dd00);
    }

    for(int i=0; i<aliens.size(); i++){
        SDL_FillRect(screen, &aliens[i].rect, 0x006d6d6d);
    }

    SDL_Flip(screen);

}

void Quit(){
    SDL_Quit();
}
