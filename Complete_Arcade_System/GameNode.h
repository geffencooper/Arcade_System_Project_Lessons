// GameNode.h

#include "Node.h"
#include "Config.h"
#include "SimpleGame.h"


class GameNode : public Node
{
    public: 
        GameNode(SDL_Renderer* renderer_in, Node* parentNode_in): Node(renderer_in, parentNode_in)
        {
            SimpleGame* game = new SimpleGame;
            //game->addTextureToScreen(createImage(renderer_in, "brickBreakerNodeImages/brickBreakerScreen.png", true));

            Ball* ball = new Ball;
            ArcadeTexture* ballTexture = createImage(renderer_in, "brickBreakerNodeImages/ballTexture.png");

            ball->setGameObjectTexture(ballTexture);
            ball->setState(true);

            game->addEntity(ball);
            game->addMovingEntity(ball);
            game->setBall(ball);

            game->setisNewGame(true);
            game->setGameState(true);

            this->addScreen(game);
            this->setCurrentScreen(game);
        }
};