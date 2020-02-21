// TetrisNode.h

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

				Map* newMap = new Map(30,10,16,renderer_in);
				// each  outer bracket is the row and each inner is the column

				// 2 ++++++++++++++++++++++++++++
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
	
				this->addScreen(game);
				this->setCurrentScreen(game);
			}
	};