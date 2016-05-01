#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject
{
    public:
        Bullet(int x, int y);
        void Move();
};

#endif // BULLET_H
