// HighscoresNode.h

// resources we need to build the highscores node
#include "Node.h"
#include "MenuScreen.h"
#include "SimpleButton.h"
#include "Config.h"

class HighscoresNode : public Node // inherits from node
{
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
	}
};
