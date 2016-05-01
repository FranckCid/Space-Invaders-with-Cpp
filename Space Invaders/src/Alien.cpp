#include "Alien.h"

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
