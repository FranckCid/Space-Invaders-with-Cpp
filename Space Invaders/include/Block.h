#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"

class Block : public GameObject
{
    public:
        unsigned int life;
        Block();
        bool Damage();
};

#endif // BLOCK_H
