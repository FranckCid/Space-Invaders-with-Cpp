#include "Block.h"

#include "GameObject.h"

Block::Block(int x, int y, int t)
{
    isAlive = true;
    life = 4;
    rect = {x, y, 25, 25};
    type = t;
}

void Block::Damage(){
    if(life > 0){
        life--;
        return;
    }
    isAlive = false;
}

