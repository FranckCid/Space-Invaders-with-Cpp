#include "Alien.h"
#include "AlienBullet.h"

#include <vector>
#include <iostream>

Alien::Alien(){
    rect = {25, 25, 25, 25};
    dirx = 1;
    diry = 1;
}

Alien::Alien(int x, int y){
    rect = {x, y, 25, 25};
    dirx = 1;
    diry = 1;
}

void Alien::Move(int x, int y){
    rect.x += x;
    rect.y += y;
}

void Alien::Shot(std::vector<AlienBullet> &ls){
    std::cout << "ASDASASD";
    ls.push_back(AlienBullet(rect.x, rect.y));
}
