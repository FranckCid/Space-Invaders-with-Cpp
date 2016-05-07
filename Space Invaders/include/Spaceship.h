#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <vector>

#include "GameObject.h"
#include "Bullet.h"

#include <SDL/SDL.h>

class Spaceship : public GameObject
{
    public:
        int lifes, score;
        Spaceship();
        void Shot(std::vector<Bullet> &ls);
        void Damage();
};

#endif // SPACESHIP_H
