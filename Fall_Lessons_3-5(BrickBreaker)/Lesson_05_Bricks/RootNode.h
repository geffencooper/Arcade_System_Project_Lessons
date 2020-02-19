// RootNode 

// include the files we need
#include "Node.h"
#include "Config.h"
#include "MenuScreen.h" 
#include "SimpleButton.h" 
#include "GameNode.h"
    
class RootNode : public Node // publicly inherits from Node
{
private:
GameNode* gameNode;

public:
    // Constructor                                            // initializer list
    RootNode(SDL_Renderer* renderer_in, Node* parentNode_in): Node(renderer_in, parentNode_in)
    {
        gameNode = new GameNode(getRenderer(), this);
        children.push_back(gameNode);
        // first create screens for the node
        MenuScreen* screen1 = createMenuScreen();
    
        // create images and text to put on the screen using an ArcadeTexture object
        ArcadeTexture* screen1Background = createImage(renderer_in, "rootNodeImages/rootNodeScreenBackground.png", true);

        ArcadeTexture* screen1Text = createSimpleText(renderer_in, "fonts/retro/italic.ttf", 100, "MAIN MENU", 255, 255, 0);
        screen1Text->setPosition(windowWidth / 2 - screen1Text->getWidth() / 2, 25);

        // add the images and text to the screen after creating them
        screen1->addTextureToScreen(screen1Background);
        screen1->addTextureToScreen(screen1Text);
    
        // make a text button to put on the screen1
        SimpleButton* button1 = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "PLAY SIMPLE GAME", 255, 0, 0);
        button1->setButtonPosition(windowWidth / 2 - button1->getWidth() / 2, screen1Text->getY() + screen1Text->getHeight() + 50);

        // give this button an action
        button1->setButtonAction(createAction(MOVE_NODES, gameNode));
        
        // add the buttons to their screens
        screen1->addButtonToScreen(button1);
    
        // add the screens to the node
        this->addScreen(screen1);

        // tell the node the current screen
        this->setCurrentScreen(screen1);
    }
};
