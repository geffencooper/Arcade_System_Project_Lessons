// Paddle.h

#ifndef PADDLE_H
#define PADDLE_H

#include "Entity.h"

class Paddle : public Entity
{
public:
	Paddle();
	void update(SDL_Event* event);
};

#endif