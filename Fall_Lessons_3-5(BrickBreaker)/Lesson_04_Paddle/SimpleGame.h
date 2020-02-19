// SimpleGame.h

#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H

#include "GameScreen.h"
#include "Ball.h"
#include "Config.h"

// need to include the paddle class
#include "Paddle.h"

class SimpleGame : public GameScreen
{
    public:
        SimpleGame();
        Action update(SDL_Event* event);
        void logic();

        void newGame();

        void setBall(Ball* ball_in) {ball = ball_in;}
        Ball* getBall() {return ball;}
        
        // accessor and mutator methods
        void setPaddle(Paddle* paddle_in) {paddle = paddle_in;}
        Paddle* getPaddle() {return paddle;}
    private:
        Ball* ball;
        // add paddle as an attribute of the game
        Paddle* paddle;
};

#endif