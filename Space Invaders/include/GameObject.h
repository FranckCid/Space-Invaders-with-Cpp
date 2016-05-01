#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL/SDL.h>

class GameObject
{
    public:
        int dirx, diry;
        SDL_Rect rect;
        GameObject();
        void Move(int velx, int vely);
        bool Intersects(SDL_Rect r);
};

#endif // GAMEOBJECT_H
