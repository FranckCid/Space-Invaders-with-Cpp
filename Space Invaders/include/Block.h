#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"

class Block : public GameObject
{
    public:
        unsigned int life, type;
        Block(int x, int y, int type);
        void Damage();
};

#endif // BLOCK_H
