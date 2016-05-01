#include "Bullet.h"

Bullet::Bullet(int x, int y)
{
    rect = {x, y, 5, 10};
}

void Bullet::Move(){
    rect.y -= 10;
}
