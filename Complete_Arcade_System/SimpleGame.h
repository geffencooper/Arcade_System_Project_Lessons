// SimpleGame.h

#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H

#include "GameScreen.h"
#include "Ball.h"
#include "Config.h"

class SimpleGame : public GameScreen
{
    public:
        SimpleGame();
        Action update(SDL_Event* event);
        void logic();

        void newGame();
        

        void setBall(Ball* ball_in) {ball = ball_in;}
        Ball* getBall() {return ball;}
    private:
        Ball* ball;
};

#endif