#include "GameObject.h"

#include <SDL/SDL.h>

GameObject::GameObject()
{
    isAlive = true;
    rect.x = 20;
    rect.y = 250;
    rect.h = 200;
    rect.w = 200;
}

void GameObject::Move(int velx, int vely){
    rect.x += velx;
    rect.y += vely;
}

bool GameObject::Intersects(SDL_Rect r){
    if((rect.x >= r.x && rect.y >= r.y && rect.x <= r.x+r.w && rect.y <= r.y+r.h) ||
       (r.x >= rect.x && r.y >= rect.y && r.x <= rect.x+rect.w && r.y <= rect.y+rect.h)){
        return true;
    }
    return false;
}

