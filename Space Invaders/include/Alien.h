#ifndef ALIEN_H
#define ALIEN_H

#include "GameObject.h"
#include "Bullet.h"
#include "AlienBullet.h"

#include <vector>

class Alien : public GameObject
{
    public:
        Alien();
        Alien(int x, int y);
        void Move();
        void Move(int x, int y);
        void Shot(std::vector<AlienBullet> &ls);
};

#endif // ALIEN_H
