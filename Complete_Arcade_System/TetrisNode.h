// GameNode.h

	#include "Node.h"
	#include "Config.h"
	#include "TetrisGame.h"
	
	class TetrisNode : public Node
	{
		public: 
			TetrisNode(SDL_Renderer* renderer_in, Node* parentNode_in): Node(renderer_in, parentNode_in)
			{
				// Create the GameScreen
				TetrisGame* game = new TetrisGame;

				// Add a background image
				game->addTextureToScreen(createImage(renderer_in, "brickBreakerNodeImages/tetrisScreen.png", true));
				
				game->gameName = "Tetris";
				game->ren = renderer_in;
				
				// initialize the game score texture
				game->gameScoreTexture = createSimpleText(renderer_in, "fonts/pixel/classic.ttf", 40, "SCORE: ", 255,0,0);
				game->gameScoreTexture->setPosition(320,20);
				game->addTextureToScreen(game->gameScoreTexture);
				

				Map* newMap = new Map(30,10,16,renderer_in);
				// each  outer bracket is the row and each inner is the column
				std::vector<std::vector<int> > longPiece =
				{
					{ 1,0,0,0 },
					{ 1,0,0,0 },
					{ 1,0,0,0 },
					{ 1,0,0,0 }
				};
				std::vector<std::vector<int> > squarePiece =
				{
					{ 1,1 },
					{ 1,1 }
				};
				std::vector<std::vector<int> > TPiece =
				{
					{ 1,0,0 },
					{ 1,1,0 },
					{ 1,0,0 }
				};
				std::vector<std::vector<int> > LPiece =
				{
					{ 1,0,0 },
					{ 1,0,0 },
					{ 1,1,0 }
				};
				std::vector<std::vector<int> > L2Piece =
				{
					{ 0,1,0 },
					{ 0,1,0 },
					{ 1,1,0 }

				};
				std::vector<std::vector<int> > zigZagPiece =
				{
				 	{ 1,0,0 },
					{ 1,1,0 },
					{ 0,1,0 }
				};
				std::vector<std::vector<int> > zigZag2Piece =
				{
				 	{ 0,1,0 },
					{ 1,1,0 },
					{ 1,0,0 }
				};
				game->pieces = {squarePiece, longPiece, LPiece, L2Piece, TPiece,zigZagPiece, zigZag2Piece};
				
				game->setMap(newMap);


				game->setisNewGame(true);
				game->setGameState(true);
	
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
				game->setGameOverScreen(gameOverScreen);
				
	//////////////////////////////////////////////////////////////////////////////
				MenuScreen* pauseScreen = createMenuScreen();
				pauseScreen->addTextureToScreen(createImage(renderer_in, "brickBreakerNodeImages/pauseScreenBackgroundTexture.png",true));
				ArcadeTexture* pauseText = createSimpleText(renderer_in, "fonts/retro/italic.ttf", 100,"PAUSE", 255, 255, 0);
				pauseText->setPosition(windowWidth / 2 - pauseText->getWidth() / 2, 25);
				pauseScreen->addTextureToScreen(pauseText);
	
	
				SimpleButton* resumeButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30,"RESUME", 255, 0, 0);
				resumeButton->setButtonPosition(windowWidth / 2 - resumeButton->getWidth() / 2, 270);
				resumeButton->setButtonAction(createAction(MOVE_SCREENS, game));
			   
				pauseScreen->addButtonToScreen(resumeButton);
				game->setPauseScreen(pauseScreen);
				
				game->setParentNode(parentNode_in);
	
				this->addScreen(game);
				this->addScreen(pauseScreen);
				this->addScreen(gameOverScreen);
	
				this->setCurrentScreen(game);
			}
	
			void enter()
			{
				SDL_RenderClear(getRenderer());
				setCurrentScreen(getScreenList()[0]);
			}
	};