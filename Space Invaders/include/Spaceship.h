#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <vector>

#include "GameObject.h"
#include "Bullet.h"

#include <SDL/SDL.h>

class Spaceship : public GameObject
{
    public:
        Spaceship();
        void Shot(std::vector<Bullet> &ls);
};

#endif // SPACESHIP_H
