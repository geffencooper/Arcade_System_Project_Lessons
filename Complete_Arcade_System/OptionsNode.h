#include "Node.h"
#include "MenuScreen.h"
#include "OptionsButton.h"
#include "SDL_mixer.h"
 
class OptionsNode : public Node
{
public:
    Mix_Music* music0 = nullptr;
    Mix_Music* music1 = nullptr;
    Mix_Music* music2 = nullptr; 
    // pass this in from main when you create it
    OptionsNode(SDL_Renderer* renderer_in = nullptr, Node* parentNode_in = nullptr) : Node(renderer_in, parentNode_in)
    {
        MenuScreen* optionsNodeScreen = createMenuScreen();
 
        ArcadeTexture* optionsNodeScreenBackground = createImage(renderer_in, "optionsNodeImages/optionsNodeScreen.png", true);
        optionsNodeScreen->addTextureToScreen(optionsNodeScreenBackground);
 
        ArcadeTexture* optionsText = createSimpleText(renderer_in, "fonts/retro/italic.ttf", 100, "OPTIONS", 255, 255, 0);
        optionsText->setPosition(windowWidth / 2 - optionsText->getWidth()/2, 20);
        optionsNodeScreen->addTextureToScreen(optionsText);
        
        OptionsButton* soundOptionButton = createOptionsButton(renderer_in, "fonts/retro/italic.ttf", 60, "SOUND", 255, 255, 0);
        soundOptionButton->setButtonPosition(50, 150);
 
        Action* soundOff = createAction(CHANGE_SOUND, 0);
        ArcadeTexture* soundOffText = createSimpleText(renderer_in, "fonts/pixel/classic.ttf", 30, "OFF", 0, 255, 0);
        soundOffText->setPosition(300, 170);
        soundOptionButton->addOption(soundOff, soundOffText);
        
        Action* soundOn = createAction(CHANGE_SOUND, 1);
        ArcadeTexture* soundOnText = createSimpleText(renderer_in, "fonts/pixel/classic.ttf", 30, "ON", 0, 255, 0);
        soundOnText->setPosition(300, 170);
        soundOptionButton->addOption(soundOn, soundOnText);
    
        OptionsButton* musicOptionButton = createOptionsButton(renderer_in, "fonts/retro/italic.ttf", 60, "MUSIC", 255, 255, 0);
        musicOptionButton->setButtonPosition(50, 250);
        
        music0 = nullptr;
        Action* noMusic = createAction(CHANGE_MUSIC, music0);
        ArcadeTexture* noMusicImage = createImage(renderer_in, "optionsNodeImages/noMusic.png");
        noMusicImage->setPosition(300, 270);
        musicOptionButton->addOption(noMusic, noMusicImage);
 
        music1 = Mix_LoadMUS("optionsNodeImages/Classy-8-Bit.wav");
        Action* intenseMusic = createAction(CHANGE_MUSIC, music1);
        ArcadeTexture* intenseMusicImage = createImage(renderer_in, "optionsNodeImages/intenseMusicOptionTexture.png");
        intenseMusicImage->setPosition(300, 270);
        musicOptionButton->addOption(intenseMusic, intenseMusicImage);
 
        music2 = Mix_LoadMUS("optionsNodeImages/Retro-80s-Technology.wav");
        Action* calmMusic = createAction(CHANGE_MUSIC, music2);
        ArcadeTexture* calmMusicImage = createImage(renderer_in, "optionsNodeImages/calmMusicOptionTexture.png", false);
        calmMusicImage->setPosition(300, 270);
        musicOptionButton->addOption(calmMusic, calmMusicImage);
 
        SimpleButton* mainMenuButton = createSimpleTextButton(renderer_in,"fonts/pixel/classic.ttf", 30, "MAIN MENU", 255,0,0);
        mainMenuButton->setButtonPosition(windowWidth / 2 - mainMenuButton->getWidth() / 2, windowHeight - 50);
        mainMenuButton->setButtonAction(createAction(MOVE_NODES, getParentNode()));
 
        optionsNodeScreen->addButtonToScreen(mainMenuButton);
        optionsNodeScreen->addButtonToScreen(soundOptionButton);
        optionsNodeScreen->addButtonToScreen(musicOptionButton);
        this->addScreen(optionsNodeScreen);
        this->setCurrentScreen(optionsNodeScreen);
    }
 
    virtual ~OptionsNode() 
    {
        printf("FREEING MUSIC FROM OPTIONS DESTRUCTOR=============\n");
        if (music1 != nullptr)
        {
            Mix_FreeMusic(music1);
            music1 = nullptr;
        }
        if (music2 != nullptr)
        {
            Mix_FreeMusic(music2);
            music2 = nullptr;
        }
    }
};