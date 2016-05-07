#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>

#include "GameObject.h"
#include "Spaceship.h"
#include "Block.h"
#include "Alien.h"
#include "Bullet.h"
#include "AlienBullet.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

//Engine variables
SDL_Surface *screen=NULL, *spritesheet=NULL;
SDL_Event event;

//Interface
TTF_Font *font=NULL;
SDL_Rect rscore, rpoints, rlives, rlifes;
SDL_Surface *sscore, *spoints, *slives;

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
    SDL_Rect pbullet, ebullet[2];
};

Sprites sprites;

//Variables
Spaceship player;
std::vector<Bullet> bullets;
std::vector<AlienBullet> ebullets;
std::vector<Block> blocks;
std::vector<Alien> aliens;

void Menu(){
    SDL_Surface *sur=NULL;
    sur = TTF_RenderText_Solid(font, "Press any button to continue", {255, 255,255,255});
    SDL_Rect nr = {30, 250, 0, 0};
    while(1){
        SDL_PollEvent(&event);
        SDL_BlitSurface(sur, NULL, screen, &nr);
        SDL_Flip(screen);
        if(event.type == SDL_KEYDOWN){
            return;
        }
    }
}

void GameOver(){
    SDL_Surface *sur=NULL;
    sur = TTF_RenderText_Solid(font, "Game Over", {255, 255,255,255});
    SDL_Rect nr = {30, 250, 0, 0};
    while(1){
        SDL_PollEvent(&event);
        SDL_BlitSurface(sur, NULL, screen, &nr);
        SDL_Flip(screen);
        if(event.type == SDL_KEYDOWN){
            return;
        }
    }
}

int main ( int argc, char** argv )
{

    const int FPS = 30;
    Uint32 start;
    float frame=0;

    Load();

    Menu();

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
    TTF_Init();

    screen = SDL_SetVideoMode(600, 500, 32, SDL_SWSURFACE);

    font = TTF_OpenFont("Munro.ttf", 32);
    sscore = TTF_RenderText_Solid(font, "Score:", {255,255,255});
    spoints = TTF_RenderText_Solid(font, "10", {255,255,255});
    slives = TTF_RenderText_Solid(font, "Lives:", {255,255,255});

    rscore = {25, 10, 200, 200};
    rpoints = {120, 10, 200, 200};
    rlives = {350, 10, 200, 200};
    rlifes = {450, 15, 200, 200};

    LoadSprites();

}

void LoadSprites(){
    spritesheet = IMG_Load("sprites/space_invaders.png");

    ResetAll();

    sprites.alien1[0] = {7, 225, 16, 16};
    sprites.alien2[0] = {74, 225, 24, 16};
    sprites.alien3[0] = {147, 225, 24, 16};

    sprites.alien1[1] = {40, 225, 16, 16};
    sprites.alien2[1] = {108, 225, 24, 16};
    sprites.alien3[1] = {178, 225, 24, 16};

    sprites.player = {277, 225, 32, 16};

    sprites.blocks[0][0] = {373, 210, 16, 16};
    sprites.blocks[0][1] = {428, 209, 16, 16};
    sprites.blocks[0][2] = {480, 210, 16, 16};
    sprites.blocks[0][3] = {316, 214, 16, 16};

    sprites.blocks[1][0] = {428+12, 209, 16, 16};
    sprites.blocks[1][1] = {373+12, 210, 16, 16};
    sprites.blocks[1][2] = {480+12, 210, 16, 16};
    sprites.blocks[1][3] = {316+12, 212, 16, 16};

    sprites.blocks[2][0] = {480+12*3, 210, 16, 16};
    sprites.blocks[2][1] = {480+12*3, 210, 16, 16};
    sprites.blocks[2][2] = {480+12*3, 210, 16, 16};
    sprites.blocks[2][3] = {480+12*3, 210, 16, 16};

    sprites.pbullet = {201, 606, 2, 10};
    sprites.ebullet[0] = {172, 609, 8, 8};
    sprites.ebullet[1] = {172, 630, 8, 8};

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

    if(keystates[SDLK_SPACE] && toshoot > 15){
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
                player.score += 500;
                char buffer[500];
                sprintf(buffer, "%d", player.score);
                std::cout << buffer << player.score << "\n";
                spoints = TTF_RenderText_Solid(font, buffer, {255,255,255});
                bullets.erase(bullets.begin() + i);
                return;
            }
        }
        if(bullets[i].rect.y < 0){
            bullets.erase(bullets.begin() + i);
            return;
        }
    }

    for(int i=0; i<ebullets.size(); i++){
        ebullets[i].Move();
        for(int j=0; j<blocks.size(); j++){
            if(ebullets[i].Intersects(blocks[j].rect)){
                blocks[j].Damage();
                ebullets.erase(ebullets.begin()+i);
                return;
            }
        }
        if(ebullets[i].Intersects(player.rect)){
            player.Damage();
            ebullets.erase(ebullets.begin()+i);
            return;
        }
        if(ebullets[i].rect.y > 700){
            ebullets.erase(ebullets.begin() + i);
            return;
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
                blocks.push_back(Block(15*i+99*k, 12*j+340, 0));
            }
        }
    }
    player.lifes = 3;
    player.score = 0;
}

void Loose(){
    std::cout << "YOU LOOSE, CHANGE SCENE\n";
    GameOver();
    ResetAll();
}

void Logic(){

    Keyboard();

    CheckUnitys();

    if(counter > 5){
        if(tick < 20){
            for(int i=0; i<aliens.size(); i++){
                aliens[i].Move(7*dirx, 0);
                if(aliens[i].rect.y > 400){
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

    if(rand()%800+1>785 && aliens[rindex].isAlive){
        aliens[rindex].Shot(ebullets);
    }

    if(player.lifes <= 0){
        Loose();
    }

    counter++;
    toshoot++;
   // std::cout << ebullets.size() << "\n";

}

void Interface(){
    SDL_BlitSurface(sscore, NULL, screen, &rscore);
    SDL_BlitSurface(spoints, NULL, screen, &rpoints);
    SDL_BlitSurface(slives, NULL, screen, &rlives);
    for(int i=0; i<player.lifes; i++){
        rlifes.x += 30;
        SDL_BlitSurface(spritesheet, &sprites.player, screen, &rlifes);
    }
    rlifes.x = 400;
}

void DrawScreen(){

    SDL_FillRect(screen, NULL, 0);

    SDL_BlitSurface(spritesheet, &sprites.player, screen, &player.rect);

    for(int i=0; i<bullets.size(); i++){
        SDL_BlitSurface(spritesheet, &sprites.pbullet, screen, &bullets[i].rect);
    }

    for(int i=0; i<ebullets.size(); i++){
        SDL_BlitSurface(spritesheet, &sprites.ebullet[rand()%2], screen, &ebullets[i].rect);
    }

    for(int i=0; i<blocks.size(); i++){
        if(blocks[i].life > 0){
            SDL_BlitSurface(spritesheet, &sprites.blocks[1][blocks[i].life-1], screen, &blocks[i].rect);
        }
    }

    for(int i=0; i<aliens.size(); i++){
        if(aliens[i].isAlive){
            if(i <= 22){
                SDL_BlitSurface(spritesheet, &sprites.alien1[rand()%2], screen, &aliens[i].rect);
            }else if(i > 22 && i <= 43){
                SDL_BlitSurface(spritesheet, &sprites.alien2[rand()%2], screen, &aliens[i].rect);
            }else if(i > 43 && i <= 55){
                SDL_BlitSurface(spritesheet, &sprites.alien3[rand()%2], screen, &aliens[i].rect);
            }
        }
    }

    Interface();

    SDL_Flip(screen);

}

void Quit(){
    SDL_FreeSurface(spritesheet);
    SDL_FreeSurface(screen);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
