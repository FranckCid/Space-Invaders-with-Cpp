#ifndef ALIEN_H
#define ALIEN_H

#include "GameObject.h"

class Alien : public GameObject
{
    public:
        Alien();
        Alien(int x, int y);
        void Move();
        void Move(int x, int y);
};

#endif // ALIEN_H
