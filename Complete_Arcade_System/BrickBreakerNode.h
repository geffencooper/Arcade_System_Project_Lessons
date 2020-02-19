// BrickBreakerNode.h

#include "Node.h"
#include "Config.h"
#include "BrickBreakerGame.h"


class BrickBreakerNode : public Node
{
    public: 
        BrickBreakerNode(SDL_Renderer* renderer_in, Node* parentNode_in): Node(renderer_in, parentNode_in)
        {
            // Create the GameScreen
            BrickBreakerGame* game = new BrickBreakerGame;

            // add a background image
            game->addTextureToScreen(createImage(renderer_in, "brickBreakerNodeImages/brickBreakerScreen.png", true));

            game->gameName = "BrickBreaker";
            game->ren = renderer_in;
            
            // initialize the game score texture
            game->gameScoreTexture = createSimpleText(renderer_in, "fonts/pixel/classic.ttf", 30, "SCORE: ", 255,0,0);
            game->gameScoreTexture->setPosition(0,0);
            game->addTextureToScreen(game->gameScoreTexture);

            // create and initialize the ball object
            Ball* ball = new Ball;
            ArcadeTexture* ballTexture = createImage(renderer_in, "brickBreakerNodeImages/ballTexture.png");
            ballTexture->setPosition(0, 0);
            ball->setGameObjectTexture(ballTexture);

            game->addEntity(ball);
            game->addMovingEntity(ball);
            game->setBall(ball);

            // create and initialize the paddle object
            Paddle* paddle = new Paddle;
            ArcadeTexture* paddleTexture = createImage(renderer_in, "brickBreakerNodeImages/paddleTexture.png");
            paddleTexture->setPosition(0, 0);
            paddle->setGameObjectTexture(paddleTexture);

            game->addEntity(paddle);
            game->addMovingEntity(paddle);
            game->setPaddle(paddle);

            // create and initialize all the brick objects
            for (int row = 0; row < 5; row++)
            {
                for (int col = 0; col < 10; col++)
                {
                    if (row == 0)
                    {
                        Brick* newYellowBrick = new Brick;
                        ArcadeTexture* yellowBrickTexture = createImage(renderer_in, "brickBreakerNodeImages/yellowBrickTexture.png");
                        yellowBrickTexture->setPosition(70 + col * 50, 50 + row * 20);
                        newYellowBrick->setGameObjectTexture(yellowBrickTexture);
                        game->addEntity(newYellowBrick);
                    }
                    else if (row == 1)
                    {
                        Brick* newBlueBrick = new Brick;
                        ArcadeTexture* blueBrickTexture = createImage(renderer_in, "brickBreakerNodeImages/blueBrickTexture.png");
                        blueBrickTexture->setPosition(70 + col * 50, 50 + row * 20);
                        newBlueBrick->setGameObjectTexture(blueBrickTexture);
                        game->addEntity(newBlueBrick);
                    }
                    else if (row == 2)
                    {
                        Brick* newRedBrick = new Brick;
                        ArcadeTexture* redBrickTexture = createImage(renderer_in, "brickBreakerNodeImages/redBrickTexture.png");
                        redBrickTexture->setPosition(70 + col * 50, 50 + row * 20);
                        newRedBrick->setGameObjectTexture(redBrickTexture);
                        game->addEntity(newRedBrick);
                    }
                    else if (row == 3)
                    {
                        Brick* newGreenBrick = new Brick;
                        ArcadeTexture* greenBrickTexture = createImage(renderer_in, "brickBreakerNodeImages/greenBrickTexture.png");
                        greenBrickTexture->setPosition(70 + col * 50, 50 + row * 20);
                        newGreenBrick->setGameObjectTexture(greenBrickTexture);
                        game->addEntity(newGreenBrick);
                    }
                    else if (row == 4)
                    {
                        Brick* newYellowBrick = new Brick;
                        ArcadeTexture* yellowBrickTexture = createImage(renderer_in, "brickBreakerNodeImages/yellowBrickTexture.png");
                        yellowBrickTexture->setPosition(70 + col * 50, 50 + row * 20);
                        newYellowBrick->setGameObjectTexture(yellowBrickTexture);
                        game->addEntity(newYellowBrick);
                    }
                }
            }

            game->setGameState(true);
            game->setisNewGame(true);

            this->addScreen(game);

            // create and initialize and the pause screen
            MenuScreen* pauseScreen = createMenuScreen();
            pauseScreen->addTextureToScreen(createImage(renderer_in, "brickBreakerNodeImages/pauseScreenBackgroundTexture.png", true));
            ArcadeTexture* pauseText = createSimpleText(renderer_in, "fonts/retro/italic.ttf", 100,"PAUSE", 255, 255, 0);
            pauseText->setPosition(windowWidth / 2 - pauseText->getWidth() / 2, 25);
            pauseScreen->addTextureToScreen(pauseText);


            SimpleButton* resumeButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30,"RESUME", 255, 0, 0);
            resumeButton->setButtonPosition(windowWidth / 2 - resumeButton->getWidth() / 2, 270);
            resumeButton->setButtonAction(createAction(MOVE_SCREENS, game));
            pauseScreen->addButtonToScreen(resumeButton);

            this->addScreen(pauseScreen);
        
            // create and initialize the gameOver screen
            MenuScreen* gameOverScreen = createMenuScreen();
            gameOverScreen->addTextureToScreen(createImage(renderer_in, "brickBreakerNodeImages/pauseScreenBackgroundTexture.png", true));
            ArcadeTexture* gameOverText = createSimpleText(renderer_in, "fonts/retro/italic.ttf", 100, "GAME OVER", 255, 255, 0);
            gameOverText->setPosition(windowWidth / 2 - gameOverText->getWidth() / 2, 25);
            gameOverScreen->addTextureToScreen(gameOverText);

            SimpleButton* mainMenuButton2 = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30,"GAME MENU", 255, 0, 0);
            mainMenuButton2->setButtonPosition(windowWidth / 2 - mainMenuButton2->getWidth() / 2, 200);
            mainMenuButton2->setButtonAction(createAction(MOVE_NODES, getParentNode()));
            gameOverScreen->addButtonToScreen(mainMenuButton2);

            SimpleButton* newGameButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "NEW GAME", 255, 0, 0);
            newGameButton->setButtonPosition(windowWidth / 2 - newGameButton->getWidth() / 2, 270);
            newGameButton->setButtonAction(createAction(MOVE_SCREENS, game));
            gameOverScreen->addButtonToScreen(newGameButton);

            this->addScreen(gameOverScreen);
            this->setCurrentScreen(game);

            game->setGameOverScreen(gameOverScreen);
            game->setPauseScreen(pauseScreen);

            game->setParentNode(getParentNode());
        }

        void enter()
        {
            setCurrentScreen(getScreenList()[0]);
        }
};