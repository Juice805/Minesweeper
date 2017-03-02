//
//  main.cpp
//  Minesweeper
//
//  Created by Justin Oroz on 10/22/14.
//  Copyright (c) 2014 jmoroz. All rights reserved.
//


// create minefield
// create scanfield
// fill minefield with mines in random locations (How Many?)
// fill remaining minefield with corresponding numbers (diagonal counts)
//

#include "main.h"
#include "juice.h"
#include "Minesweeper.h"

// Main ****************************************************************

int main(int argc, const char * argv[]) {
    int boardsize, columns = 0, rows = 0;
    bool play = true, moveOn, square = false;
    string answer,size, board, board2;
    Minesweeper game;
    
    do {
        moveOn = false;
        while (!moveOn) {
            if (!game.isReplayed()) {
                cout << "\nType \"help\" for information\nInput board size: \n";
                cin >> board;
            }
            
            
            game.clearscreen();
            
            if (stringtolower(board) == "help") {
                cout << "\nEnter size [rows] [colums], or [size] for square boards\n";
                moveOn = false;
                cin.ignore(INT_MAX,'\n');
                cin.clear();
            }else if (game.isReplayed()){ // if a replay, just skip getting input
                moveOn = true;
            }else { //only gets new values on a new game
                while (isspace(cin.peek()) && cin.peek() != '\n') {
                    cin.get();
                }
                if (cin.peek() != '\n') {
                    cin >> board2;
                    square = false;
                } else square = true;
                
                cin.ignore(INT_MAX,'\n');
                cin.clear();
                
                if (square) {
                    rows = atoi(board.c_str());
                    columns = rows;
                } else {
                    rows = atoi(board.c_str());
                    columns = atoi(board2.c_str());
                }
                
                boardsize = rows * columns;
                
                if (boardsize < 16 || rows < 3 || columns < 3) {
                    if (boardsize > 0)
                        cout << "Try something harder! Enter a new number\n";
                    else cout << "Enter a valid number\n";
                    moveOn = false;
                } else moveOn = true;
            }
        }
        
        
        
        game.startGame(rows,columns);
        
        
        if (!game.quit && !game.restart) {
            //  play = prompt("Play Again?");
            
            string response;
            bool validResponse = false;
            bool answer;
            
            cout << endl << "Play Again?" << " (y/n) or \"replay\"\n";
            do {
                cin >> response;
                cin.ignore(INT_MAX,'\n');
                cin.clear();
                
                if (stringtolower(response) == "replay") {
                    game.replay();
                    validResponse = true;
                    answer = true;
                } else if (tolower(response[0]) == 'y') {
                    validResponse = true;
                    answer = true;
                } else if (tolower(response[0]) == 'n') {
                    validResponse = true;
                    answer = false;
                } else {
                    cout << "\nPlease enter a valid response (y/n)\n";
                    validResponse = false;
                    answer = false;
                }
            } while (!validResponse);
            
            play = answer;
            
            
            if (!play)
                cout << "\nExiting...\n";
        }
        if (!game.isReplayed()) { //if they dont want to replay the board
            game.clearBoard();  //clear it
        }

    } while (play && !game.quit);
    
    
    return 0;
}
