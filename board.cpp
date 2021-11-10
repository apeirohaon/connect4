using namespace std;

#include "board.h"

void Board::PrintBoard() {
    for (int i = 1; i < ylen + 1; i++) {
        for (int j = 1; j < xlen + 1; j++) {
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void Board::PrintWholeBoard() {
    for (int i = 0; i < xlen + 2; i++) {
        for (int j = 0; j < ylen + 2; j++) {
            cout << board[j][i] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void Board::SaveToFile(std::ofstream &file) {
    for (int i = 1; i < ylen + 1; i++) {
        for (int j = 1; j < xlen + 1; j++) {
            file << board[i][j];
        }
    }
}

void Board::LoadFromFile(std::ifstream &file) {
    for (int i = 1; i < ylen + 1; i++) {
        for (int j = 1; j < xlen + 1; j++) {
            file >> board[i][j];
        }
    }
}

bool Board::ColumnFilled(int x) {
    if (board[1][x] == '_') {
        return false;
    }
    return true;
}

void Board::DropPiece(int x, char colour) {
    for (int i = 1; i <= ylen; i++) {
        if (!(board[i + 1][x] == '_') || ((i == ylen) && (board[i][x] == '_'))) {
            board[i][x] = colour;
            lastMovePosX = x;
            lastMovePosY = i;
            return;
        }
    }
}

char Board::CheckWin(bool fromPos) {
    //checks for a win which includes the last made move
    if (fromPos) {
        if (CheckAround(lastMovePosX, lastMovePosY)) {
            return board[lastMovePosY][lastMovePosX];
        }
        return 'X';
    }
    
    // checks for a win on the entire board (very inefficiently)
    for (int i = 1; i < xlen + 1; i++) {
        for (int j = 1; j < ylen + 1; j++) {
            if (CheckAround(i, j)) {
                return board[j][i];
            }
        }
    }
    return 'X';
}

bool Board::CheckAround(int x, int y) {
    return (
        (CheckInLine(x, y, -1, 1, 1) + CheckInLine (x, y, 1, -1, 0) >= 4) ||
        (CheckInLine(x, y, -1, 0, 1) + CheckInLine (x, y, 1, 0, 0) >= 4) ||
        (CheckInLine(x, y, -1, -1, 1) + CheckInLine (x, y, 1, 1, 0) >= 4) ||
        (CheckInLine(x, y, 0, 1, 1) + CheckInLine (x, y, 0, -1, 0) >= 4)
    );
}

//recursively sees how many connected pieces there are in the specified direction (xDir,yDir), starting from the specified coordinates (x,y)
int Board::CheckInLine(int x, int y, const int xDir, const int yDir, int currInRow) {
    int checkPosX = x + xDir;
    int checkPosY = y + yDir;
    if (board[checkPosY][checkPosX] == playerToMove) {
        return CheckInLine(checkPosX, checkPosY, xDir, yDir, currInRow + 1);
    }
    return currInRow;
}