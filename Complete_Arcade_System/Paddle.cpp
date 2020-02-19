// Paddle.cpp 

#include "Paddle.h"

Paddle::Paddle()
{
	setXPos(0);
	setYPos(0);
	setXVelocity(0);
	setYVelocity(0);
}

void Paddle::update(SDL_Event* event)
{
	if ((event) && ((*event).type == SDL_KEYDOWN) && (*event).key.repeat == 0)
	{
		switch ((*event).key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			printf("\nRIGHT\n");
			setXVelocity(getXVelocity() + 8);
			break;
		}
		case SDLK_LEFT:
		{
			printf("\nLEFT\n");
			setXVelocity(getXVelocity() - 8);
			break;
		}
		}
	}
	else if ((event != nullptr) && (*event).type == SDL_KEYUP && (*event).key.repeat == 0)
	{
		switch ((*event).key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			setXVelocity(getXVelocity()-8);
			break;
		}
		case SDLK_LEFT:
		{
			setXVelocity(getXVelocity()+8);
			break;
		}
		}
	}
	if (!event)
	{
		setXPos(getXPos() + getXVelocity());
	}
}