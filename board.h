#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

class Board {
    public:
        Board(int x, int y)
            : playerToMove('R'), gameEnd(false), xlen(x), ylen(y), row(xlen + 2, '_'), board(ylen + 2, row) //private variable initialization
        {}
        void PrintBoard();
        void PrintWholeBoard(); //for debugging, includes the buffer around the playable board area
        bool ColumnFilled(int x); //checks if a column is filled
        void DropPiece(int x, char colour); //drops a piece into a given column, in the first row without a piece already in it
        char CheckWin(bool fromPos); //returns the color of the winning player or else 'X' (if there is no win)
        int GetBoardDimensionX() { return xlen; }
        int GetBoardDimensionY() { return ylen; }
        char GetPlayerToMove() { return playerToMove; } 
        bool GetGameEnd() { return gameEnd; }
        void SetPlayerToMove(char ptm) { playerToMove = ptm; }
        void SetGameEnd(bool end) { gameEnd = end; }
        void SaveToFile(std::ofstream &file);
        void LoadFromFile(std::ifstream &file);
    private:
        char playerToMove;
        bool gameEnd;
        int xlen;
        int ylen;
        std::vector<char> row;
        std::vector< std::vector<char> > board;
        int lastMovePosX;
        int lastMovePosY;
        bool CheckAround(int x, int y); //for checking for a win
        int CheckInLine(int x, int y, const int xDir, const int yDir, int currInRow); //for CheckAround
};