// SimpleGame.h

#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H

#include "GameScreen.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
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

        void setPaddle(Paddle* paddle_in) {paddle = paddle_in;}
        Paddle* getPaddle() {return paddle;}

    private:
        Ball* ball;
        Paddle* paddle;
};

#endif
