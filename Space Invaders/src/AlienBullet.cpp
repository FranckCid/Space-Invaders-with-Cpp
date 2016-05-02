#include "AlienBullet.h"
#include "GameObject.h"

AlienBullet::AlienBullet(int x, int y){
    rect = {x, y, 10, 20};
}

void AlienBullet::Move(){
    rect.y += 10;
}
