// HighscoresNode.h

// resources we need to build the highscores node
#include "Node.h"
#include "MenuScreen.h"
#include "SimpleButton.h"
#include "Config.h"
#include "iostream"
#include "fstream"

using std::ofstream;
using std::ifstream;
using std::getline;

class HighscoresNode : public Node // inherits from node
{
private:
	std::vector<ArcadeTexture*> brickBreakerScoreTextures;
	std::vector<ArcadeTexture*> tetrisScoreTextures;
	std::vector<ArcadeTexture*> froggerScoreTextures;
public:
	// CONSTRUCTOR
    	// pass these parameters (renderer and parent node) in from main when you create a RootNode object
	HighscoresNode(SDL_Renderer* renderer_in = nullptr, Node* parentNode_in = nullptr) : Node(renderer_in, parentNode_in)
	{
		// ====================================== ROOT NODE INITIALIZATION =========================================
     
       		// ----------------------------------------SCREEN CREATION
       		// first create a MenuScreen object
		MenuScreen* highscoresScreen = createMenuScreen();
		
		// create an image to put on the screen using an ArcadeTexture object
		ArcadeTexture* highscoresNodeScreenBackground = createImage(renderer_in, "highscoresNodeImages/highscoresNodeScreenBackground.png", true);
		highscoresScreen->addTextureToScreen(highscoresNodeScreenBackground);
		
		// create text to put on the screen using an ArcadeTexture object, initialize its position
		ArcadeTexture* highscoresText = createSimpleText(renderer_in, "fonts/retro/italic.ttf",100, "HIGHSCORES", 255, 255, 0);
		highscoresText->setPosition(windowWidth / 2 - highscoresText->getWidth() / 2, 20);
		highscoresScreen->addTextureToScreen(highscoresText);
		//---------------------------------------------------------------------------------------
		
		//---------------------------------------------------- BUTTON CREATION
      		// MAIN MENU BUTTON
                // make a simple button that will take you to the main menu node
		SimpleButton* mainMenuButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "MAIN MENU",255, 0, 0);
		mainMenuButton->setButtonPosition(windowWidth / 2 - mainMenuButton->getWidth() / 2, windowHeight - 50);
		mainMenuButton->setButtonAction(createAction(MOVE_NODES, getParentNode()));
		highscoresScreen->addButtonToScreen(mainMenuButton);

		this->addScreen(highscoresScreen);
		this->setCurrentScreen(highscoresScreen);
		//-------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------------------------
		ifstream fileIn;
		fileIn.open("BrickBreaker.txt");
		if (fileIn.fail())
		{
			ofstream fileOut;
			fileOut.open("BrickBreaker.txt", std::ios_base::app);
			fileOut << "BRICKBREAKER\n 1 ---  000\n 2 ---  000\n 3 ---  000\n 4 ---  000\n 5 ---  000\n 6 ---  000\n 7 ---  000\n 8 ---  000\n 9 ---  000\n10 ---  000";
			fileOut.close();
		}
		fileIn.close();

		fileIn.open("Tetris.txt");
		if (fileIn.fail())
		{
			ofstream fileOut;
			fileOut.open("Tetris.txt", std::ios_base::app);
			fileOut << "   TETRIS\n 1 ---  000\n 2 ---  000\n 3 ---  000\n 4 ---  000\n 5 ---  000\n 6 ---  000\n 7 ---  000\n 8 ---  000\n 9 ---  000\n10 ---  000";
			fileOut.close();
		}
		fileIn.close();

		fileIn.open("froggerScores.txt");
		if (fileIn.fail())
		{
			ofstream fileOut;
			fileOut.open("froggerScores.txt", std::ios_base::app);
			fileOut << "   FROGGER\n 1 ---  000\n 2 ---  000\n 3 ---  000\n 4 ---  000\n 5 ---  000\n 6 ---  000\n 7 ---  000\n 8 ---  000\n 9 ---  000\n10 ---  000";
			fileOut.close();
		}
		fileIn.close();

		fileIn.open("BrickBreaker.txt");
		std::string currScore = "";
		int start = 0;

		while (getline(fileIn, currScore))
		{
			ArcadeTexture* scoreTexture = createSimpleText(this->getRenderer(), "fonts/pixel/classic.ttf", 15, currScore, 255, 255, 255);
			scoreTexture->setPosition(10, 140 + start);
			getCurrentScreen()->addTextureToScreen(scoreTexture);
			brickBreakerScoreTextures.push_back(scoreTexture);
			start += 24;
		}
		fileIn.close();

		fileIn.open("Tetris.txt");
		currScore = "";
		start = 0;

		while (getline(fileIn, currScore))
		{
			ArcadeTexture* scoreTexture = createSimpleText(this->getRenderer(), "fonts/pixel/classic.ttf", 15, currScore, 255, 255, 255);
			scoreTexture->setPosition(220, 140 + start);
			getCurrentScreen()->addTextureToScreen(scoreTexture);
			tetrisScoreTextures.push_back(scoreTexture);
			start += 24;
		}
		fileIn.close();

		fileIn.open("froggerScores.txt");
		currScore = "";
		start = 0;

		while (getline(fileIn, currScore))
		{
			ArcadeTexture* scoreTexture = createSimpleText(this->getRenderer(), "fonts/pixel/classic.ttf", 15, currScore, 255, 255, 255);
			scoreTexture->setPosition(430, 140 + start);
			getCurrentScreen()->addTextureToScreen(scoreTexture);
			froggerScoreTextures.push_back(scoreTexture);
			start += 24;
		}
		fileIn.close();
	}

	void enter()
	{
		ifstream fileIn;
		fileIn.open("BrickBreaker.txt");
		std::string currScore = "";
		int i = 0;

		while (getline(fileIn, currScore))
		{
			SDL_Color c = { 255,255,255 };
			brickBreakerScoreTextures[i]->loadFromRenderedText("fonts/pixel/classic.ttf", 15, currScore, c);
			i++;
		}
		fileIn.close();

		fileIn.open("Tetris.txt");
		currScore = "";
		i = 0;

		while (getline(fileIn, currScore))
		{
			SDL_Color c = { 255,255,255 };
			tetrisScoreTextures[i]->loadFromRenderedText("fonts/pixel/classic.ttf", 15, currScore, c);
			i++;
		}
		fileIn.close();

		fileIn.open("froggerScores.txt");
		currScore = "";
		i = 0;

		while (getline(fileIn, currScore))
		{
			SDL_Color c = { 255,255,255 };
			froggerScoreTextures[i]->loadFromRenderedText("fonts/pixel/classic.ttf", 15, currScore, c);
			i++;
		}
		fileIn.close();
	}
};