// TetrisGame.cpp

#include "TetrisGame.h"

// constructor
TetrisGame::TetrisGame(){}

// functions to move pieces
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

// function to copy map into entities   
void TetrisGame::setMap(Map* m_in)
{
    // need to add all entities in map to the entity list
    m = m_in;
    for(int row = 0; row < (m->getTiles()).size(); row++)
    {
        for(int col = 0; col < (m->getTiles())[row].size(); col++)
        {
            addEntity((m->getTiles())[row][col]);
        }
    }
}

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
        printf("\n first rotation\n");
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
        int newY = -(x-a)+b-30;
        //printf("\n (%i,%i) about (%i,%i)\n", x,y,a,b);
        //printf("\n (%i,%i) to (%i,%i)\n", x,y,newX,newY);
        if(newX > 0 && newY > 0 && newX < (m->getxDim())*(m->getSideSize()) && newY < (m->getyDim())*(m->getSideSize()))
        {
            if(m->getTiles()[newY/(m->getSideSize())][newX/(m->getSideSize())]->getState() == true)
            {
                return;
            }
        }
    }
    for(int i = 0; i < piece_in.size(); i++)
    {
        x = piece_in[i]->getXPos();
        y = piece_in[i]->getYPos();
        int newX = (y-b)+a;
        int newY = -(x-a)+b-30;
        //printf("\n (%i,%i) about (%i,%i)\n", x,y,a,b);
        //printf("\n (%i,%i) to (%i,%i)\n", x,y,newX,newY);
        
        piece_in[i]->setXPos(newX);
        piece_in[i]->setYPos(newY);
    }
    
    for(int i = 0; i < piece_in.size(); i++)
    {
         x = piece_in[i]->getXPos();
         y = piece_in[i]->getYPos();
            while(x < 0)
            {
                //printf("block %i is moving from (%i,%i) to (%i,%i)",i,x,y,newX,newY);
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

// this method creates a new piece as an entity
void TetrisGame::addPiece(std::string path, point tlc, std::vector<std::vector<int> > piece)
{
    getMovingEntities().clear();

    if(tlc.x > m->getTiles()[0].size())
    {
        printf("TLC x coordinate %i out of range\n", tlc.x);
        return;
    }
    if(tlc.y > m->getTiles().size())
    {
        printf("TLC y coordinate %i out of range\n", tlc.y);
        return;
    }
    for(int row = 0; row < piece.size(); row++)
    {
        for(int col = 0; col < piece[row].size(); col++)
        {
            if(piece[row][col] == 1)
            {
                if(m->getTiles()[(tlc.y+row)][(tlc.x+col)]->getState() == true)
                {
                    setGameState(false);
                    return;
                }
                ArcadeTexture* newArcadeTexture = new ArcadeTexture;
                newArcadeTexture->setRenderer(m->getRenderer());
                newArcadeTexture->loadFromFile(path);
                newArcadeTexture->isEntireDestination = false;
                newArcadeTexture->setSize(m->getTiles()[row][col]->getWidth(), m->getTiles()[row][col]->getHeight());
                newArcadeTexture->setPosition(m->getSideSize()*(tlc.x+col), m->getSideSize()*(tlc.y+row));
                Tile* newPiece = new Tile;
                newPiece->setGameObjectTexture(newArcadeTexture);
                newPiece->setState(true);
                addEntity(newPiece);
                addMovingEntity(newPiece);
            }
        }
    }
}

Action TetrisGame::update (SDL_Event* event)
{

    if(!rowsToClear.empty())
    {
        // then bump everything down
        //printf("\n row start at: %i", rowsToClear[rowsToClear.size()-1]);
        for(int row = rowsToClear[rowsToClear.size()-1]; row >= 0; row--)
        {
            for(size_t col = 0; col < m->getTiles()[0].size(); col++)
            {
                if(rowsToClear.size() > row) // if there is no row above then go to cleared rows
                {
                    //printf("\ngrid[%i][%i] to grid[%i][%i]",row,col,rowsToClear[row],col);
                    m->getTiles()[row][col] = m->getTiles()[rowsToClear[row]][col];
                    m->getTiles()[row][col]->setState(false);
                }
            }
        }
        for(int row = rowsToClear[rowsToClear.size()-1]; row >= 0; row--)
        {
            for(size_t col = 0; col < m->getTiles()[0].size(); col++)
            {
                if(rowsToClear.size() > row) // if there is no row above then go to cleared rows
                {
                    
                }
                else
                {
                    //printf("\ngrid[%i][%i] to grid[%i][%i]",row,col,row-rowsToClear.size(),col);
                    m->getTiles()[row][col] = m->getTiles()[row-rowsToClear.size()][col];
                }
            }
        }
        for(int row = rowsToClear[rowsToClear.size()-1]; row >= 0; row--)
        {
            for(size_t col = 0; col < m->getTiles()[0].size(); col++)
            {
                m->getTiles()[row][col]->setXPos(col*30);
                m->getTiles()[row][col]->setYPos(row*30);
            }
        }
        rowsToClear.clear();
    }
    
    //printf("\nentered the game\n");
    // first check if it is a new game
    if (getIsNewGame())
	{
		newGame();
	}

    // create a default action to return
	Action newAction = { DO_NOTHING, nullptr };

    // update all the entities given by passing the event
	for (int i = 0; i < getMovingEntities().size(); i++)
	{
		getMovingEntities()[i]->update(event);
        getMovingEntities()[i]->setState(true);
	}
    // this moves the current piece down by one block every second
    // when you move an entity must edit the map before and after so that
    // current location is empty and new location is filled

        if(event)
        {
            if ((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_DOWN)
            {
                if(!getNextPiece)
                {
                    count=59;
                }
            }
            if ((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_UP && (*event).key.repeat == 0)
            {
                rotatePiece(getMovingEntities(),{30,30});
            }
            if ((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_LEFT)
            {
                moveLeft(getMovingEntities());
                rot.x -= getMovingEntities()[0]->getWidth();
            }
            else if ((*event).type == SDL_KEYDOWN &&(*event).key.keysym.sym == SDLK_RIGHT)
            {
                moveRight(getMovingEntities());
                rot.x += getMovingEntities()[0]->getWidth();
            }
        }

        if(true)
        {
            count++;
        }
        if(count == 60)
        {
            // first check if you can move the piece by checking conditions for each block
            //printf("attempt moving: \n");
            for (int i = 0; i < getMovingEntities().size(); i++)
	        {
                //printf("block %i ", i);
                // get the x and y coords of the entity
                int x = getMovingEntities()[i]->getXPos();
                int y = getMovingEntities()[i]->getYPos();

                int nextRow = (getMovingEntities()[i]->getHeight()+y)/(m->getSideSize());
                int nextCol = x/(m->getSideSize()); 
                //printf("block %i ", i);
                //printf("TLC_X %i ", x);
                //printf("TLC_Y %i ", y);
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

                    int nextRow = (getMovingEntities()[i]->getHeight()+y)/(m->getSideSize());
                    int nextCol = x/(m->getSideSize()); 

                    m->getTiles()[y/(m->getSideSize())][x/(m->getSideSize())] = (Tile*)(getMovingEntities()[i]);
                    m->getTiles()[y/(m->getSideSize())][x/(m->getSideSize())]->setState(true);
                }
                count = 0;
                return newAction;
            }
            
            
            count = 0;
        }
    
    // execute the game logic
	logic();

    // if the gameState is false end the game
	if (getgameState() == false)
	{
        submitScore(ren);
		setisNewGame(true);
		setGameState(true);
        getNextPiece = false;

		newAction = { MOVE_SCREENS, getGameOverScreen() };
		return newAction;
	}
    if(event)
    {
        if ((*event).key.keysym.sym == SDLK_q)
        {
            setisNewGame(true);
            newAction = { MOVE_NODES, getParentNode() };
            return newAction;
        }
        else if ((*event).key.keysym.sym == SDLK_p)
        {
            newAction = { MOVE_SCREENS, getPauseScreen() };
            return newAction;
        }
        else if (event && (*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_n)
        {
            setGameState(true);
            setisNewGame(true);
        }
    }
    gameScoreTexture->loadFromRenderedText("fonts/pixel/classic.ttf", 40, "Score: " + std::to_string(gameScore), { 255,0,0 });
	
	return newAction;
}

void TetrisGame::newGame()
{
        printf("\nstarting new game\n");
        m->clear();
        getMovingEntities().clear();
        getEntities().clear();
		setGameState(true);
		setisNewGame(false);
        getNextPiece = true;
        gameScore = 0;
}
	

void TetrisGame::logic()
{
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

        int rowsCleared = 0;
        for(int row = 0; row < m->getTiles().size(); row++)
        {
            int colCount = 0;
            for(int col = 0; col < m->getTiles()[0].size(); col++)
            {
                if(m->getTiles()[row][col]->getState() == true)
                {
                    colCount++;
                }
            }
            if(colCount == m->getTiles()[0].size())
            {
                rowsCleared++;
                rowsToClear.push_back(row);
            }
        }
        if(rowsCleared > 1)
            gameScore += 2*rowsCleared;
        else
            gameScore += rowsCleared;
    }
}