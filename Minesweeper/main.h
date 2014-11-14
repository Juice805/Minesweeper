//
//  main.h
//  Minesweeper
//
//  Created by Justin Oroz on 10/27/14.
//  Copyright (c) 2014 jmoroz. All rights reserved.
//

#ifndef Minesweeper_main_h
#define Minesweeper_main_h

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <ctime>
using namespace std;

class Minesweeper {
public:
    Minesweeper(int row, int col) {
        startGame(row, col); //initilized with predefined square size
    }
    Minesweeper(int size) {
        startGame(size, size); //initilized with predefined square size
    }
    Minesweeper() { //creates empty game, use startGame function
    }
    
    void startGame(int, int); // accepts only 1 integer, makes square boards only
    
    void clearBoard() { //resets board
        playing = true;
        win = false;
        restart = false;
        needHelp = false;
        firstGuess = true;
        showCredits = false;
        replayed = false;
        minefield.clear();
        scanfield.clear();
        guesses = 0;
        mines = 0;
        flags = 0;
        flag(-1, -1); //resets flag grid
    }
    
    void promptUser(); //prompts user for their input (takes care of each turn)
    void printScanfield(); //prints the board
    void clearscreen(){cout << string(100, '\n');} //empties the screen
    bool restart = false;
    void replay();
    bool isReplayed(){
        return replayed;
    }
    bool quit = false;
    void help();
    
private:
    bool needHelp = false;
    bool playing = true;
    bool win = false;
    bool printMines = false;
    bool firstGuess = true;
    bool showCredits = false;
    bool replayed = false;
    int minefieldRows;
    int minefieldColumns;
    int mines = 0;
    int guesses = 0;
    int flags = 0;
    vector< vector<bool> > minefield;
    vector< vector<char> > scanfield;
    bool getInput();
    void showBombs();
    void createMinefield();
    void printMinefield();
    void createScanfield();
    int fillMinefield();
    void checkguess(const int&, const int&);
    int surroundingBombs(const int&, const int&);
    void revealField(const int&, const int&);
    void flag(const int&, const int&);
    bool valid(const int&, const int&);
    void checkwin();
    int digits(const int&);
    string tolower(string);
};

#endif
