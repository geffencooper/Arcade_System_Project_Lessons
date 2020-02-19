// RootNode.h

// resources we need to build the root node
#include "Node.h"
#include "Config.h"
#include "MenuScreen.h" 
#include "SimpleButton.h" 
#include "HighscoresNode.h"
#include "GameMenuNode.h"
#include "OptionsNode.h"
 
class RootNode : public Node // inherits from Node
{
private:
    // CHILDREN NODE POINTERS
    // every node has pointers to its children, define these classes before you create pointers to objects of these classes
    HighscoresNode* highscoresNode; 
    GameMenuNode* gameMenuNode;
    OptionsNode* optionsNode;
 
public:
    // CONSTRUCTOR
    // pass these parameters (renderer and parent node) in from main when you create a RootNode object
    RootNode(SDL_Renderer* renderer_in = nullptr, Node* parentNode_in = nullptr): Node(renderer_in, parentNode_in)
    {
        // CREATE CHILDREN
        // first create the children nodes of the root on the heap and store them in pointers we declared above
        // when we create the children nodes, their constructors will be called before the rest of this constructor is executed.
        highscoresNode = new HighscoresNode(getRenderer(), this);
        gameMenuNode = new GameMenuNode(getRenderer(), this);
        optionsNode = new OptionsNode(getRenderer(), this);
        
        // after the constructors for the three nodes above are executed, the rest of the code below is executed
     
        // STORE THE CHILDREN NODE POINTERS
        // every node has a list called "children" to hold its children nodes. This list is called a vector.
        // use the method "push_back" to add node pointer elements to the vector as shown. Here we add pointers to the children nodes
        children.push_back(highscoresNode);
        children.push_back(gameMenuNode);
        children.push_back(optionsNode);
 
        // ====================================== ROOT NODE INITIALIZATION =========================================
     
        // ----------------------------------------SCREEN CREATION
        // first create a MenuScreen object
        MenuScreen* rootNodeScreen = createMenuScreen();
 
        // create an image to put on the screen using an ArcadeTexture object
        ArcadeTexture* rootNodeScreenBackground = createImage(renderer_in, "rootNodeImages/rootNodeScreenBackground.png", true);
        rootNodeScreen->addTextureToScreen(rootNodeScreenBackground);
 
        // create text to put on the screen using an ArcadeTexture object, initialize its position
        ArcadeTexture* mainMenuText = createSimpleText(renderer_in, "fonts/retro/italic.ttf", 100, "MAIN MENU", 255, 255, 0);
        mainMenuText->setPosition(windowWidth / 2 - mainMenuText->getWidth() / 2, 25);
        rootNodeScreen->addTextureToScreen(mainMenuText);
        //---------------------------------------------------------------------------------------
     
     
        //---------------------------------------------------- BUTTON CREATION
        // HIGHSCORES BUTTON
        // make a simple button that will take you to the highscores node
        SimpleButton* highscoresButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "HIGHSCORES", 255, 0, 0);
        highscoresButton->setButtonPosition(windowWidth / 2 - highscoresButton->getWidth() / 2,
                                            mainMenuText->getY() + mainMenuText->getHeight() + 50);
        // link this button to the highscoresNode by creating an action and passing the highscoresNode pointer as the action parameter
        highscoresButton->setButtonAction(createAction(MOVE_NODES, highscoresNode));
        
        // GAME MENU BUTTON
        // make a simple button that will take you to the gameMenu node
        SimpleButton* gameMenuButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "GAME MENU", 255, 0, 0);
        gameMenuButton->setButtonPosition(windowWidth / 2 - gameMenuButton->getWidth() / 2,
                                          highscoresButton->getY() + highscoresButton->getHeight() + 25);
        // link this button to the gameMenuNode by creating an action and passing the gameMenuNode pointer as the action parameter
        gameMenuButton->setButtonAction(createAction(MOVE_NODES, gameMenuNode));
 
        // OPTIONS BUTTON
        // make a simple button that will take you to the options node
        SimpleButton* optionsButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "OPTIONS", 255, 0, 0);
        optionsButton->setButtonPosition(windowWidth / 2 - optionsButton->getWidth() / 2, 
                                         gameMenuButton->getY() + gameMenuButton->getHeight() + 25);
        // link this button to the optionsNode by creating an action and passing the optionsNode pointer as the action parameter
        optionsButton->setButtonAction(createAction(MOVE_NODES, optionsNode));
        //---------------------------------------------------------------------------------------------------------------
        
     
        // ------------------------------------------ BUTTON, SCREEN, NODE LINK ---------------------------------------------
        // BUTTON->SCREEN
        // add all the buttons to their according screen
        rootNodeScreen->addButtonToScreen(highscoresButton);
        rootNodeScreen->addButtonToScreen(gameMenuButton);
        rootNodeScreen->addButtonToScreen(optionsButton);
        
        // SCREEN->NODE
        // add the screen to the node and set the starting screen you want
        this->addScreen(rootNodeScreen);
        this->setCurrentScreen(rootNodeScreen);
    }
};