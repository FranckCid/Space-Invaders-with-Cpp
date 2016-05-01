#include "Block.h"

#include "GameObject.h"

Block::Block()
{
    life = 10;
    rect = {250, 250, 20, 20};
}

bool Block::Damage(){
    if(life >=1){
        life--;
        return false;
    }
    return true;
}

