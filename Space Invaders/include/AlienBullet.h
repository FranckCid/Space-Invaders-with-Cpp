#ifndef ALIENBULLET_H
#define ALIENBULLET_H

#include "Bullet.h"

class AlienBullet : public GameObject
{
    public:
        AlienBullet(int x, int y);
        void Move();
};

#endif // ALIENBULLET_H
