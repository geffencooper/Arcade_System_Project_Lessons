// SimpleGame.cpp

#include "SimpleGame.h"

SimpleGame::SimpleGame()
{
    //
}

// game logic
Action SimpleGame::update(SDL_Event* event)
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
        setisNewGame(true);
        setGameState(true);
        getBall()->setXVelocity(0);
        getBall()->setYVelocity(0);

        newAction = {MOVE_SCREENS, getGameOverScreen()};
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

void SimpleGame::newGame()
{
    setGameState(true);
    ball->setXPos(0);
    ball->setYPos(0);
    ball->setXVelocity(2);
    ball->setYVelocity(5);
    paddle->setXPos(0);
    paddle->setYPos(windowHeight-paddle->getHeight());
    paddle->setXVelocity(0);
    setisNewGame(false);
}

void SimpleGame::logic()
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
}
