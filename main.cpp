/*
Noah Cheff
Lab 6: Semester Project
09 May 2021
Windows 10 Home Version 20H2, compiled with g++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>

using namespace std;

#include "board.h"

int Menu();
void Game(Board &board);
int Turn(Board &board);
void SwitchPlayerToMove(Board &board);
int SaveFile(string filename, Board &board);
int LoadFile(string filename, Board &board);
bool IsStringNumeric(string st);

int main() {
    int status;
    while (status == 0) {
        status = Menu();
    }
    cout << "Exiting." << endl;
    return 0;
}

int Menu() {
    int opt;
    cout << "1 : Start New Game" << endl
         << "2 : Load Game From File" << endl
         << "3 : Exit" << endl << endl;
    cin >> opt;
    cout << endl;

    if (opt == 1) { //newgame
        /*
        --- this made the saving/loading harder so I scrapped it for now in favor of fixing board dimensions to 7,6
        int xdim, ydim;
        cout << "Please enter the dimensions you would like your game board to have." << endl << endl;
        cout << "Number of rows: ";
        cin >> ydim;
        cout << "Number of columns: ";
        cin >> xdim;
        cout << endl << endl;
        */

        cout << "Game is starting." << endl;
        cout << "On any turn, type \"s\" to save the current board to a file or \"q\" to exit the game (does not save automatically)." << endl << endl;

        this_thread::sleep_for(2200ms);

        Board board(7, 6);
        Game(board);

        cout << endl << "Returning to menu." << endl << endl;
        return 0;
    }

    if (opt == 2) { //load game
        Board board(7, 6);
        string filename;
        cout << "What file would you like to load from? ";
        cin >> filename;
        int status = LoadFile(filename, board);

        if (status == 0) { Game(board); }

        cout << endl << "Returning to menu." << endl << endl;
        return 0;
    }

    if (opt == 3) { //quit
        return 1;
    }

    return 2;
}

void Game(Board &board) {
    int status;

    //the main loop, keeps going until there is a win on the board or user quits
    while (!board.GetGameEnd()) {
        board.PrintBoard();
        status = Turn(board);
    }
    
    if (status == 2) {
        //runs once the game ends
        board.PrintBoard();
        cout << "Game over!" << endl;
        cout << "Player " << board.GetPlayerToMove() << " wins!" << endl;
    }
    
    if (status == 3) {
        cout << "Game has exited." << endl;
    }
}

int Turn(Board &board) {
    string move;
    bool ask = true;

    //keeps asking for a move until a valid one (non-filled column) is entered
    while (ask) {
        cout << "Turn: " << board.GetPlayerToMove() << endl;
        cout << "Enter the column in which you wish to place your piece: ";
        cin >> move;
        cout << endl;

        if (!IsStringNumeric(move)) {
            if (move == "s") {
                string filename;
                cout << "What file would you like to save to? ";
                cin >> filename;
                SaveFile(filename, board);
                cout << endl << endl;

                return 1;
            }
            else if (move == "q") {
                board.SetGameEnd(true);
                return 3;
            }
            else {
                cout << "#Error: Please enter a number." << endl << endl;
            }
        }
        else if (stoi(move) < 1 || stoi(move) > board.GetBoardDimensionX()) {
            cout << "#Error: Please enter a valid column number, from 1 to " << board.GetBoardDimensionX() << "." << endl << endl;
        }
        else if (board.ColumnFilled(stoi(move))) {
            cout << "#Invalid: This column is filled. Please enter a different column." << endl << endl;
        }
        else {
            ask = false;
        }
    }

    board.DropPiece(stoi(move), board.GetPlayerToMove());

    if (board.CheckWin(true) != 'X') { // if the previous move caused that player to win
        board.SetGameEnd(true);
        return 2;
    } 

    SwitchPlayerToMove(board);

    return 0;
}

void SwitchPlayerToMove(Board &board) {
    if (board.GetPlayerToMove() == 'R') { board.SetPlayerToMove('Y'); }
    else { board.SetPlayerToMove('R'); }
}

int SaveFile(string filename, Board &board) {
    /*
    --- ignore..
    bool found = false;
    int i = 0;
    string file;
    while (!found) {
        string next = "save" + to_string(i);
        if (!filesystem::exists(next)) {
            file = next;
            found = true;
        }
        else {
            i++;
        }
    }
    */
    ofstream outdata;
    outdata.open(filename);

    if (!outdata) {
        cerr << "Error: file could not be written to." << endl;
        return 1;
    }

    board.SaveToFile(outdata);
    return 0;
}

int LoadFile(string filename, Board &board) {
    ifstream indata;
    indata.open(filename);

    if (!indata) {
        cerr << "Error: file could not be opened." << endl;
        return 1;
    }

    board.LoadFromFile(indata);
    return 0;
}

bool IsStringNumeric(string st) {
    bool numeric = true;
    for (int i = 0; i < st.length(); i++) {
        if (!isdigit(st[i])) {
            numeric = false;
        }
    }
    return numeric;
}