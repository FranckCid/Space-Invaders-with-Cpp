#include "GameObject.h"
#include "Spaceship.h"
#include "Bullet.h"

#include <vector>

#include <SDL/SDL.h>

Spaceship::Spaceship(){
    isAlive = true;
    lifes = 3;
    score = 0;
    rect.x = 450;
    rect.y = 450;
    rect.h = 25;
    rect.w = 25;
}

void Spaceship::Shot(std::vector<Bullet> &ls){
    ls.push_back(Bullet(rect.x+13, rect.y));
}

void Spaceship::Damage(){
    lifes--;
}


