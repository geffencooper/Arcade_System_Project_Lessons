// TetrisGame.cpp
#include "TetrisGame.h"

void TetrisGame::addPiece(std::string path, point tlc, std::vector<std::vector<int> > piece)
{
    getMovingEntities().clear();
    for(int row = 0; row < piece.size(); row++)
    {
        for(int col = 0; col < piece[row].size(); col++)
        {
            if(piece[row][col] == 1)
            {
                ArcadeTexture* newArcadeTexture = new ArcadeTexture;
                newArcadeTexture->setRenderer(m->getRenderer());
                newArcadeTexture->loadFromFile(path);
                newArcadeTexture->isEntireDestination = false;
                newArcadeTexture->setSize(m->getSideSize(), m->getSideSize());
                newArcadeTexture->setPosition(m->getSideSize()*(tlc.x+col),
                m->getSideSize()*(tlc.y+row));
                Tile* newPiece = new Tile;
                newPiece->setGameObjectTexture(newArcadeTexture);
                newPiece->setState(true);
                addEntity(newPiece);
                addMovingEntity(newPiece);
            }
        }
    }
}

void TetrisGame::setMap(Map* m_in)
{
    m = m_in;
    for(int row = 0; row < (m->getTiles()).size(); row++)
    {
        for(int col = 0; col < (m->getTiles())[row].size(); col++)
        {
            addEntity((m->getTiles())[row][col]);
        }
    }
}

Action TetrisGame::update(SDL_Event* event)
{
    if(getIsNewGame())
    {
        newGame();
    }

    Action newAction = {DO_NOTHING, nullptr};

    if(event)
    {
        if((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_DOWN)
        {
            if(!getNextPiece)
            {
                count=59;
            }
        }
        else if((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_UP)
        {
            // 1 +++++++++++++++++++++
            rotatePiece(getMovingEntities(), {30,30});
        }
        else if((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_LEFT)
        {
            // 1 +++++++++++++++++++++
            moveLeft(getMovingEntities());
            rot.x -= getMovingEntities()[0]->getWidth();
        }
        else if((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_RIGHT)
        {
            // 1 +++++++++++++++++++++
            moveRight(getMovingEntities());
            rot.x += getMovingEntities()[0]->getWidth();
        }
    }

    
    // count tracks the frame, every second we move down (inconsistent because some frames faster than others)
    // this is simple and don't need a timer, can use timer if you want
    // 2 +++++++++++++++++++++
    count++;
    if(count == 60)
    {
        // first check if you can move the piece by checking conditions for each block
        for (int i = 0; i < getMovingEntities().size(); i++)
        {
            // get the x and y coords of the entity
            int x = getMovingEntities()[i]->getXPos();
            int y = getMovingEntities()[i]->getYPos();

            int nextRow = (getMovingEntities()[i]->getHeight()+y)/(m->getSideSize());
            int nextCol = x/(m->getSideSize()); 
            // if the next position is the bottom or another piece, get another piece
            
            if(
                (nextRow == m->getyDim())
                    ||
                ((m->getTiles()[nextRow][nextCol]->getState() == true)) // hit a non moving block because a moving piece can have a tile above another moving tile which is valid
            )
                {
                    printf("\ncan't move so--new piece\n");
                    getNextPiece = true;
                }
            printf("\n\n");
        }
        // if all blocks can move then move them
        if(!getNextPiece)
        {
            moveDown(getMovingEntities());
            rot.y += getMovingEntities()[0]->getHeight();
        }
        else
        {
            // otherwise set all blocks to the map
            for (int i = 0; i < getMovingEntities().size(); i++)
            {
                //printf("placing block %i", i);
                // get the x and y coords of the entity
                int x = getMovingEntities()[i]->getXPos();
                int y = getMovingEntities()[i]->getYPos();

                m->getTiles()[y/(m->getSideSize())][x/(m->getSideSize())] = (Tile*)(getMovingEntities()[i]);
                m->getTiles()[y/(m->getSideSize())][x/(m->getSideSize())]->setState(true);
            }
            count = 0;
            return newAction;
        }
        count = 0;
    }
    logic();
    return newAction;
}

void TetrisGame::newGame()
{
    // 2 +++++++++++++++++++++
    //addPiece("brickBreakerNodeImages/yellowBrickTexture.png", {0,0}, pieces.at(0));
    setisNewGame(false);
    getNextPiece = true;
}

void TetrisGame::logic()
{
    // 2 +++++++++++++++++++++
    if(getNextPiece)
    {
        if(pieceIndex == pieces.size())
        {
            pieceIndex = 0;
        }
        point p1 = {0,0};
        switch(pieceIndex)
        {
            case(0):
            {
                addPiece("brickBreakerNodeImages/yellowBrickTexture.png", p1, pieces.at(pieceIndex));
                break;
            }
            case(1):
            {
                addPiece("brickBreakerNodeImages/blueBrickTexture.png", p1, pieces.at(pieceIndex));
                break;
            }
            case(2):
            {
                addPiece("brickBreakerNodeImages/redBrickTexture.png", p1, pieces.at(pieceIndex));
                break;
            }
            case(3):
            {
                addPiece("brickBreakerNodeImages/redBrickTexture.png", p1, pieces.at(pieceIndex));
                break;
            }
            case(4):
            {
                addPiece("brickBreakerNodeImages/purpleBrickTexture.png", p1, pieces.at(pieceIndex));
                break;
            }
            case(5):
            {
                addPiece("brickBreakerNodeImages/greenBrickTexture.png", p1, pieces.at(pieceIndex));
                break;
            }
            case(6):
            {
                addPiece("brickBreakerNodeImages/greenBrickTexture.png", p1, pieces.at(pieceIndex));
                break;
            }
        }
        
        pieceIndex++;
        getNextPiece = false;
        hasRotated = false;
    }
}

bool TetrisGame::moveLeft(std::vector<Entity*>& piece)
{
    for(int i = 0; i < getMovingEntities().size(); i++)
    {
        int x = getMovingEntities()[i]->getXPos();
        int y = getMovingEntities()[i]->getYPos();

        int nextCol = (x-getMovingEntities()[i]->getWidth())/(m->getSideSize());
        int nextRow = y/(m->getSideSize());
        if(nextCol < 0)
        {
            return false;
        }
    }
    for(int i = 0; i < getMovingEntities().size(); i++)
    {
        getMovingEntities()[i]->setXPos(getMovingEntities()[i]->getXPos() - getMovingEntities()[i]->getWidth());
    }
}

bool TetrisGame::moveRight(std::vector<Entity*>& piece)
{
    for(int i = 0; i < getMovingEntities().size(); i++)
    {
        int x = getMovingEntities()[i]->getXPos();
        int y = getMovingEntities()[i]->getYPos();

        int nextCol = (x+getMovingEntities()[i]->getWidth())/(m->getSideSize());
        int nextRow = y/(m->getSideSize());
        if(nextCol == m->getxDim())
        {
            return false;
        }
    }
    for(int i = 0; i < getMovingEntities().size(); i++)
    {
        getMovingEntities()[i]->setXPos(getMovingEntities()[i]->getXPos() + getMovingEntities()[i]->getWidth());
    }
}

bool TetrisGame::moveDown(std::vector<Entity*>& piece)
{
    for(int i = 0; i < getMovingEntities().size(); i++)
    {
        int x = getMovingEntities()[i]->getXPos();
        int y = getMovingEntities()[i]->getYPos();

        int nextCol = (x/m->getSideSize());
        int nextRow = (y+getMovingEntities()[i]->getHeight())/(m->getSideSize());
        if(nextRow == m->getyDim())
        {
            return false;
        }
    }
    for(int i = 0; i < getMovingEntities().size(); i++)
    {
        getMovingEntities()[i]->setYPos(getMovingEntities()[i]->getYPos() + getMovingEntities()[i]->getHeight());
    }
}

bool TetrisGame::moveUp(std::vector<Entity*>& piece)
{
    for(int i = 0; i < getMovingEntities().size(); i++)
    {
        int x = getMovingEntities()[i]->getXPos();
        int y = getMovingEntities()[i]->getYPos();

        int nextCol = (x/m->getSideSize());
        int nextRow = (y-getMovingEntities()[i]->getHeight())/(m->getSideSize());
        if(nextRow < 0)
        {
            return false;
        }
    }
    for(int i = 0; i < getMovingEntities().size(); i++)
    {
        getMovingEntities()[i]->setYPos(getMovingEntities()[i]->getYPos() - getMovingEntities()[i]->getHeight());
    }
}

// 1 +++++++++++++++++++++
void TetrisGame::rotatePiece(std::vector<Entity*>& piece_in, point rot_in)
{
    // x and y start as the top left corner the first time we rotate
    int x = piece_in[0]->getXPos();
    int y = piece_in[0]->getYPos();
    
    // a and b are the pivot coordinates and are some distance away from the TLC
    int a = x + rot_in.x;
    int b = y + rot_in.y;

    // if this is the first rotation then the pivot is just (a,b)
    if(!hasRotated)
    {
        rot = {a,b};
        hasRotated = true;
    }
    else // if this is not the first time, then the pivot is the current rot which gets updated with movement
    {
        a = rot.x;
        b = rot.y;
    }
    
    // for every block, the new TLC is rotated accordingly
    for(int i = 0; i < piece_in.size(); i++)
    {
        x = piece_in[i]->getXPos();
        y = piece_in[i]->getYPos();
        int newX = (y-b)+a;
        int newY = -(x-a)+b;//-m->getSideSize();
        printf("(%i,%i) --> (%i,%i)",newX,newY);
        // check if this new TLC is valid, if off the screen deal with it later
        if(newX > 0 && newY > 0 && newX < (m->getxDim())*(m->getSideSize()) && newY < (m->getyDim())*(m->getSideSize()))
        {
            // if on the screen but over another piece then don't rotate
            if(m->getTiles()[newY/(m->getSideSize())][newX/(m->getSideSize())]->getState() == true)
            {
                return;
            }
        }
    }
    // valid rotation so we adjust each pieces position
    for(int i = 0; i < piece_in.size(); i++)
    {
        x = piece_in[i]->getXPos();
        y = piece_in[i]->getYPos();
        int newX = (y-b)+a;
        int newY = -(x-a)+b-30;
        
        piece_in[i]->setXPos(newX);
        piece_in[i]->setYPos(newY);
    }
    
    // for pieces that were rotated off screen, adjust their position
    for(int i = 0; i < piece_in.size(); i++)
    {
         x = piece_in[i]->getXPos();
         y = piece_in[i]->getYPos();
        while(x < 0)
        {
            x+=m->getSideSize();
            moveRight(getMovingEntities());
        }
        while(x > (m->getxDim()-1)*(m->getSideSize()))
        {
            x-=m->getSideSize();
            moveLeft(getMovingEntities());
        }
        while(y < 0)
        {
            y+=m->getSideSize();
            moveDown(getMovingEntities());
        }
        while(y >= (m->getyDim()-1)*m->getSideSize())
        {
            y-=m->getSideSize();
            moveUp(getMovingEntities());
        }
    }
}

