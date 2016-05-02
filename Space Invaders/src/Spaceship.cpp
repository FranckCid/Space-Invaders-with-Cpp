#include "GameObject.h"
#include "Spaceship.h"
#include "Bullet.h"

#include <vector>

#include <SDL/SDL.h>

Spaceship::Spaceship(){
    lifes = 3;
    rect.x = 450;
    rect.y = 450;
    rect.h = 25;
    rect.w = 25;
}

void Spaceship::Shot(std::vector<Bullet> &ls){
    ls.push_back(Bullet(rect.x, rect.y));
}

void Spaceship::Damage(){
    lifes--;
}


