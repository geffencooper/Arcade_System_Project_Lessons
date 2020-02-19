// TetrisGame.h

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "GameScreen.h"
#include "Map.h"

class TetrisGame : public GameScreen
{
    public:
        TetrisGame();
        Action update(SDL_Event* event);
        void logic();
        void setMap(Map* m);
        void addPiece(std::string path, point tlc, std::vector<std::vector<int> > piece);
        void newGame();
        void rotatePiece(std::vector<Entity*>& piece, point rot_in);
        bool moveLeft(std::vector<Entity*>& piece);
        bool moveRight(std::vector<Entity*>& piece);
        bool moveDown(std::vector<Entity*>& piece);
        bool moveUp(std::vector<Entity*>& piece);

        std::vector<std::vector<std::vector<int> > > pieces;
    
    private:
        Map* m;
        // a vector of "bitmaps" which are each 2D vectors
        
        std::vector<int> rowsToClear;
        bool getNextPiece;
        int pieceIndex = 0;
        int count = 0;
        point rot;
        bool hasRotated = false;
};

#endif