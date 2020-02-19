// Brick.h

#ifndef BRICK_H
#define BRICK_H

#include "Entity.h"

class Brick : public Entity
{
    public:
        Brick();
        void update(SDL_Event* event);
};
#endif