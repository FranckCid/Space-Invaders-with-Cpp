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
#include <SDL/SDL_image.h>

//Engine variables
SDL_Surface *screen=NULL, *spritesheet=NULL;
SDL_Event event;

//Game Methods
void LoadSprites();
void Keyboard();
void CheckUnitys();
void ResetAll();

//Engine methods
void Load();
void Logic();
void DrawScreen();
void Quit();

//SPRITES
struct Sprites{
    SDL_Rect alien1[2], alien2[2], alien3[2];
    SDL_Rect player;
    SDL_Rect blocks[3][4];
};

Sprites sprites;

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
    IMG_Init(IMG_INIT_PNG);

    screen = SDL_SetVideoMode(600, 500, 32, SDL_SWSURFACE);

    LoadSprites();

}

void LoadSprites(){
    spritesheet = IMG_Load("sprites/space_invaders.png");

    ResetAll();

    sprites.alien1[0] = {7, 225, 16, 16};
    sprites.alien2[0] = {74, 225, 24, 16};
    sprites.alien3[0] = {147, 225, 24, 16};
    sprites.player = {277, 225, 32, 16};
    sprites.blocks[0][0] = {373, 210, 12, 12};
    sprites.blocks[0][1] = {428, 209, 12, 12};
    sprites.blocks[0][2] = {480, 210, 12, 12};
    sprites.blocks[0][3] = {316, 212, 12, 12};

    sprites.blocks[1][0] = {428+12, 209, 12, 12};
    sprites.blocks[1][1] = {373+12, 210, 12, 12};
    sprites.blocks[1][2] = {480+12, 210, 12, 12};
    sprites.blocks[1][3] = {316+12, 212, 12, 12};

    sprites.blocks[2][0] = {480+12*3, 210, 12, 12};
    sprites.blocks[2][1] = {480+12*3, 210, 12, 12};
    sprites.blocks[2][2] = {480+12*3, 210, 12, 12};
    sprites.blocks[2][3] = {480+12*3, 210, 12, 12};
}

int tick=0, counter=0, dirx=1, toshoot=0;
void Keyboard(){
    const Uint8 *keystates = SDL_GetKeyState(NULL);

    if(keystates[SDLK_a]){
        player.Move(-10, 0);
    }else if(keystates[SDLK_d]){
        player.Move(10, 0);
    }

    if(player.rect.x < 10){
        player.rect.x = 11;
    }else if(player.rect.x > 480){
        player.rect.x = 479;
    }

    if(keystates[SDLK_SPACE] && toshoot > 25){
        player.Shot(bullets);
        toshoot = 0;
    }
}

void CheckUnitys(){
    for(int i=0; i<bullets.size(); i++){
        bullets[i].Move();
        for(int j=0; j<blocks.size(); j++){
            if(bullets[i].Intersects(blocks[j].rect) && blocks[j].life > 0){
                blocks[j].Damage();
                bullets.erase(bullets.begin()+i);
                return;
            }
        }
        for(int j=0; j<aliens.size(); j++){
            if(aliens[j].isAlive && bullets[i].Intersects(aliens[j].rect)){
                aliens[j].isAlive = false;
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
                blocks[j].Damage();
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
}

void ResetAll(){
    aliens.clear();
    bullets.clear();
    blocks.clear();
    ebullets.clear();
    for(int j=0; j<5; j++){
        for(int i=0; i<11; i++){
            aliens.push_back(Alien(35*i+35, 35*j+35));
        }
    }
    for(int k=1; k<5; k++){
        for(int j=0; j<4; j++){
            for(int i=0; i<4; i++){
                blocks.push_back(Block(20*i+99*k, 20*j+340, 0));
            }
        }
    }
}

void Loose(){
    std::cout << "YOU LOOSE, CHANGE SCENE\n";
    ResetAll();
}

void Logic(){

    Keyboard();

    CheckUnitys();

    if(counter > 5){
        if(tick < 20){
            for(int i=0; i<aliens.size(); i++){
                aliens[i].Move(7*dirx, 0);
                if(aliens[i].rect.y > 200){
                    Loose();
                }
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

    unsigned int rindex = rand()%aliens.size();

    if(rand()%800+1>788 && aliens[rindex].isAlive){
        aliens[rindex].Shot(ebullets);
    }

    counter++;
    toshoot++;
   // std::cout << ebullets.size() << "\n";

}


void DrawScreen(){

    SDL_FillRect(screen, NULL, 0);

    SDL_BlitSurface(spritesheet, &sprites.player, screen, &player.rect);

    for(int i=0; i<bullets.size(); i++){
        SDL_FillRect(screen, &bullets[i].rect, 253);
    }

    for(int i=0; i<ebullets.size(); i++){
        SDL_FillRect(screen, &ebullets[i].rect, 253);
    }

    for(int i=0; i<blocks.size(); i++){
        if(blocks[i].life > 0){
            if(i%10>7){
                SDL_BlitSurface(spritesheet, &sprites.blocks[1][blocks[i].life-1], screen, &blocks[i].rect);
            }else if(i%10<3){
                SDL_BlitSurface(spritesheet, &sprites.blocks[1][blocks[i].life-1], screen, &blocks[i].rect);
            }else{
                SDL_BlitSurface(spritesheet, &sprites.blocks[1][blocks[i].life-1], screen, &blocks[i].rect);
            }
        }
    }

    for(int i=0; i<aliens.size(); i++){
        if(aliens[i].isAlive){
            if(i <= 22){
                SDL_BlitSurface(spritesheet, &sprites.alien1[0], screen, &aliens[i].rect);
            }else if(i > 22 && i <= 43){
                SDL_BlitSurface(spritesheet, &sprites.alien2[0], screen, &aliens[i].rect);
            }else if(i > 43 && i <= 55){
                SDL_BlitSurface(spritesheet, &sprites.alien3[0], screen, &aliens[i].rect);
            }
        }
        //SDL_FillRect(screen, &aliens[i].rect, 0x006d6d6d);
    }

    SDL_Flip(screen);

}

void Quit(){
    SDL_FreeSurface(spritesheet);
    SDL_FreeSurface(screen);
    IMG_Quit();
    SDL_Quit();
}
