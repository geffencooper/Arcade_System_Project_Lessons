// BrickBreakerGame.cpp

#include "BrickBreakerGame.h"
#include <string>

BrickBreakerGame::BrickBreakerGame()
{
    //
}

// game logic
Action BrickBreakerGame::update(SDL_Event* event)
{
    // check if new game
    if(getIsNewGame())
    {
        newGame();
    }

    // create an action object
    Action newAction = {DO_NOTHING, nullptr};
    
    // update all the game objects
    for(int i = 0; i < getMovingEntities().size(); i++)
    {
        getMovingEntities()[i]->update(event);
    }

    // execute game logic
    logic();

    // if the game state is false, end the game
    if(getgameState() == false)
    {
		submitScore(ren);
        setisNewGame(true);
        setGameState(true);
        getBall()->setXVelocity(0);
        getBall()->setYVelocity(0);
        newAction = {MOVE_SCREENS, getGameOverScreen()};
        return newAction;
    }

    if(event)
    {
        if((*event).key.keysym.sym == SDLK_q)
        {
            setisNewGame(true);
            newAction = {MOVE_NODES, getParentNode()};
            return newAction;
        }

        else if((*event).key.keysym.sym == SDLK_p)
        {
            newAction = {MOVE_SCREENS, getPauseScreen()};
            return newAction;
        }

        else if((*event).key.keysym.sym == SDLK_n)
        {
            setGameState(true);
            setisNewGame(true);
        }

        return newAction;
    }
}

void BrickBreakerGame::newGame()
{
	gameScore = 0;
	conseqHits = 1;
	hasHitPaddle = false;
    setGameState(true);
    ball->setXPos(0);
    ball->setYPos(0);
    ball->setXVelocity(2);
    ball->setYVelocity(5);
    paddle->setXPos(0);
	paddle->setYPos(windowHeight-paddle->getHeight());
	getPaddle()->setXVelocity(0);
    for (int j = 0; j < getEntities().size(); j++)
	{
		getEntities()[j]->setState(true);
	}
    setisNewGame(false);
}

bool ccw(point A, point B, point C)
{
	return ((B.y - A.y) * (C.x - B.x) - (A.x - B.x) * (B.y - C.y)) > 0;
}

bool intersect(point A, point B, point C, point D)
{
	return ccw(A, C, D) != ccw(B, C, D) && ccw(A, B, C) != ccw(A, B, D);
}

void BrickBreakerGame::logic()
{
    // ball hits left side of screen
    if(getBall()->getXPos() < 0)
    {
        getBall()->setXPos(0);
        getBall()->setXVelocity(-(getBall()->getXVelocity()));
    }

    // ball hits top of screen
    else if(getBall()->getYPos() < 0)
    {
        getBall()->setYPos(0);
        getBall()->setYVelocity(-(getBall()->getYVelocity()));
    }

    // ball hits right side of screen
    else if(getBall()->getXPos() + getBall()->getWidth() > windowWidth)
    {
        getBall()->setXPos(windowWidth - getBall()->getWidth());
        getBall()->setXVelocity(-(getBall()->getXVelocity()));
    }

    // ball hits bottom of screen
    else if(getBall()->getYPos() + getBall()->getHeight() > windowHeight)
    {
        // getBall()->setYPos(windowHeight - getBall()->getHeight());
        // getBall()->setYVelocity(-(getBall()->getYVelocity()));
        setGameState(false);
    }

    // -----------------------------------------------------------

    // paddle collisions
    SDL_Rect ballRegion = getBall()->getGameObjectTexture()->getImageDestination();
	SDL_Rect paddleRegion = getPaddle()->getGameObjectTexture()->getImageDestination();

	if (SDL_HasIntersection(&ballRegion, &paddleRegion))
	{
		hasHitPaddle = true;
		conseqHits = 1;
		getBall()->setYPos(480 - getBall()->getHeight() - getPaddle()->getHeight());
		getBall()->setYVelocity(-(getBall()->getYVelocity()));

		int ratio = (getBall()->getXPos() + getBall()->getWidth() / 2) - (getPaddle()->getXPos() + getPaddle()->getWidth() / 2);
		ball->setXVelocity(ratio / 4);
	}

    if(paddle->getXPos() < 0)
    {
        paddle->setXPos(0);
    }
    if(paddle ->getXPos() + paddle->getWidth() > windowWidth)
    {
        paddle->setXPos(windowWidth-paddle->getWidth());
    }

    //=============================================================
    //=============================================================
    //=============================================================
    //=============================================================

    int maxCollisionArea = 0;
	int maxIndex = -1;
	int w_max = 0;
	int h_max = 0;
	int j;
	int numFalse = 0;

	// find the brick with the largest collision area
	for (j = 2; j < getEntities().size(); j++)
	{
        // if collided then state should be false, keep track so know when game over
		if (getEntities()[j]->getState() == false)
		{
			numFalse += 1;
			continue;
		}

		SDL_Rect ballRegion = ball->getGameObjectTexture()->getImageDestination();
		SDL_Rect brickRegion = getEntities()[j]->getGameObjectTexture()->getImageDestination();

		if (SDL_HasIntersection(&ballRegion, &brickRegion))
		{
			SDL_Rect collisionRect;
			SDL_IntersectRect(&ballRegion, &brickRegion, &collisionRect);
			int w = collisionRect.w;
			int h = collisionRect.h;
			if (h * w > maxCollisionArea)
			{
				maxCollisionArea = h * w;
				maxIndex = j;
				w_max = w;
				h_max = h;
			}

		}
	}
	j = maxIndex;

    // if set ball position
	bool hasMoved = false;

	// for that brick with the largest collision area do the following:
	if (j >= 2)
	{
		if (hasHitPaddle)
		{
			gameScore += 1;
		}
		else
		{
			gameScore += conseqHits;
			conseqHits += 1;
		}
        Brick* currentBrick = (Brick*)getEntities()[j];
		// first find the corner of the ball that collided
		int xCorner = 0;
		int yCorner = 0;
		currentBrick->setState(false);

		//BRC:  
		if (ball->getXPos() < currentBrick->getXPos() && // 1. ball left side is to the left of the brick left side
			ball->getXPos() + ball->getWidth() > currentBrick->getXPos() &&  // 2. ball right side is to the right of the brick left side
			ball->getYPos() < currentBrick->getYPos() && // 3. ball top side is above brick top side,
			ball->getYPos() + ball->getHeight() > currentBrick->getYPos()) // 4. ball bottom side is below the brick top side
		{
			xCorner = ball->getXPos() + ball->getWidth();
			yCorner = ball->getYPos() + ball->getHeight();
		}

		//TRC:
		else if (ball->getXPos() < currentBrick->getXPos() && // 1. ball left side is to the left of the brick left side
			ball->getXPos() + ball->getWidth() > currentBrick->getXPos() &&  // 2. ball right side is to the right of the brick left side
			ball->getYPos() < currentBrick->getYPos() + currentBrick->getHeight() && // 3. ball top side is above the brick bottom side
			ball->getYPos() + ball->getHeight() > currentBrick->getYPos() + currentBrick->getHeight()) // 4. ball bottom side is below brick bottom side
		{
			xCorner = ball->getXPos() + ball->getWidth();
			yCorner = ball->getYPos();
		}

		// BLC:
		else if (ball->getXPos() < currentBrick->getXPos() + currentBrick->getWidth() && // 1. ball left side is to the left of the brick right side
			ball->getXPos() + ball->getWidth() > currentBrick->getXPos() + currentBrick->getWidth() && // 2. ball right side is to the right of the brick right side
			ball->getYPos() < currentBrick->getYPos() && // 3. ball top side is above brick top side,
			ball->getYPos() + ball->getHeight() > currentBrick->getYPos()) // 4. ball bottom side is below the brick top side
		{
			xCorner = ball->getXPos();
			yCorner = ball->getYPos() + ball->getHeight();
		}

		// TLC:
		else if (ball->getXPos() < currentBrick->getXPos() + currentBrick->getWidth() && // 1. ball left side is to the left of the brick right side
			ball->getXPos() + ball->getWidth() > currentBrick->getXPos() + currentBrick->getWidth() && // 2. ball right side is to the right of the brick right side
			ball->getYPos() < currentBrick->getYPos() + currentBrick->getHeight() && // 3. ball top side is above the brick bottom side
			ball->getYPos() + ball->getHeight() > currentBrick->getYPos() + currentBrick->getHeight()) // 4. ball bottom side is below brick bottom side
		{
			xCorner = ball->getXPos();
			yCorner = ball->getYPos();
		}
		//---------------------------

		// if two corners collide then one of the following is true
		else if (ball->getXPos() + ball->getWidth() > currentBrick->getXPos() && // ball right side right of brick left side
			ball->getXPos() < currentBrick->getXPos()) // ball left side left of brick left side
		{
			ball->setXPos(ball->getXPos() - w_max);
			ball->setXVelocity(-(ball->getXVelocity()));
			hasMoved = true;
		}
		else if (ball->getXPos() + ball->getWidth() > currentBrick->getXPos() + currentBrick->getWidth() && // ball right side right of brick right side
			ball->getXPos() < currentBrick->getXPos() + currentBrick->getWidth()) // ball left side left of brick right side
		{
			ball->setXPos(ball->getXPos() + w_max);
			ball->setXVelocity(-(ball->getXVelocity()));
			hasMoved = true;
		}
		else if (ball->getYPos() + ball->getHeight() > currentBrick->getYPos() && // ball bottom side is below brick top side
			ball->getYPos() < currentBrick->getYPos()) // ball top side above brick top side
		{
			ball->setYPos(ball->getYPos() - h_max);
			ball->setYVelocity(-(ball->getYVelocity()));
			hasMoved = true;
		}
		else if (ball->getYPos() + ball->getHeight() > currentBrick->getYPos() + currentBrick->getHeight() && // ball bottom side is below brick bottom side
			ball->getYPos() < currentBrick->getYPos() + currentBrick->getHeight()) // ball top side is above brick bottom side
		{
			ball->setYPos(ball->getYPos() + h_max);
			ball->setYVelocity(-(ball->getYVelocity()));
			hasMoved = true;
		}

        // prior position
		int xPosTemp = xCorner - ball->getXVelocity();
		int yPosTemp = yCorner - ball->getYVelocity();

        // is right on the line
		if (yPosTemp == currentBrick->getYPos() && !hasMoved)
		{
			ball->setYPos(ball->getYPos() - h_max);
			ball->setYVelocity(-(ball->getYVelocity()));
			hasMoved = true;
		}
		else if (yPosTemp == currentBrick->getYPos() + currentBrick->getHeight() && !hasMoved)
		{
			printf("on the line: \n");
			ball->setYPos(ball->getYPos() + h_max);
			ball->setYVelocity(-(ball->getYVelocity()));
			hasMoved = true;
		}
		else if (xPosTemp == currentBrick->getXPos() + currentBrick->getWidth() && !hasMoved)
		{
			printf("on the line: \n");
			ball->setXPos(ball->getXPos() + w_max);
			ball->setXVelocity(-(ball->getXVelocity()));
			hasMoved = true;
		}
		else if (xPosTemp == currentBrick->getXPos() && !hasMoved)
		{
			printf("on the line: \n");
			ball->setXPos(ball->getXPos() - w_max);
			ball->setXVelocity(-(ball->getXVelocity()));
			hasMoved = true;
		}

		point ball_init = { xPosTemp, yPosTemp };
		point ball_final = { xCorner, yCorner };

		point R_TLC = { currentBrick->getXPos(), currentBrick->getYPos() };
		point R_TRC = { currentBrick->getXPos() + currentBrick->getWidth(), currentBrick->getYPos() };
		point R_BLC = { currentBrick->getXPos(), currentBrick->getYPos() + currentBrick->getHeight() };
		point R_BRC = { currentBrick->getXPos() + currentBrick->getWidth(), currentBrick->getYPos() + currentBrick->getHeight() };

		// intersects top
		if (!hasMoved && intersect(ball_init, ball_final, R_TLC, R_TRC))
		{
			ball->setYPos(ball->getYPos() - h_max);
			ball->setYVelocity(-(ball->getYVelocity()));
		}

		// intersects bottom
		else if (!hasMoved && intersect(ball_init, ball_final, R_BLC, R_BRC))
		{
			ball->setYPos(ball->getYPos() + h_max);
			ball->setYVelocity(-(ball->getYVelocity()));
		}

		// intersects left
		else if (!hasMoved && intersect(ball_init, ball_final, R_TLC, R_BLC))
		{
			ball->setXPos(ball->getXPos() - w_max);
			ball->setXVelocity(-(ball->getXVelocity()));
		}

		// intersects right
		else if (!hasMoved && intersect(ball_init, ball_final, R_TRC, R_BRC))
		{
			ball->setXPos(ball->getXPos() + w_max);
			ball->setXVelocity(-(ball->getXVelocity()));
		}
		else if (h_max == w_max)
		{
			ball->setXPos(ball->getXPos() - ball->getXVelocity());
			ball->setYPos(ball->getYPos() - ball->getYVelocity());
			ball->setXVelocity(-(ball->getXVelocity()));
			ball->setYVelocity(-(ball->getYVelocity()));
		}

		if (hasHitPaddle)
		{
			hasHitPaddle = false;
		}
	}
	gameScoreTexture->loadFromRenderedText("fonts/pixel/classic.ttf", 25, "Score: " + std::to_string(gameScore), { 255,0,0 });
	if (numFalse == 50)
		setGameState(false);
}