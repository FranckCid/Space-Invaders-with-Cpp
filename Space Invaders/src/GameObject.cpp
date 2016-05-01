#include "GameObject.h"

#include <SDL/SDL.h>

GameObject::GameObject()
{
    rect.x = 20;
    rect.y = 250;
    rect.h = 200;
    rect.w = 200;
}

void GameObject::Move(int velx, int vely){
    rect.x += velx;
    rect.y += vely;
}

