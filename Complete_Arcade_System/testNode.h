#include "Node.h"
#include "Config.h"
#include "MenuScreen.h" 
#include "SimpleButton.h" 

class TestNode : public Node
{
    public:
    // CONSTRUCTOR
    // pass these parameters (renderer and parent node) in from main when you create a RootNode object
    TestNode(SDL_Renderer* renderer_in = nullptr, Node* parentNode_in = nullptr): Node(renderer_in, parentNode_in)
    {
        MenuScreen* screen1 = createMenuScreen();
        ArcadeTexture* image1 = createImage(renderer_in, "brickBreakerNodeImages/ballTexture.png");
        screen1->addTextureToScreen(image1);
        this->addScreen(screen1);
        this->setCurrentScreen(screen1);
    }

};