//
//  Minesweeper.cpp
//  Minesweeper
//
//  Created by Justin Oroz on 3/2/17.
//  Copyright © 2017 jmoroz. All rights reserved.
//

#include "Minesweeper.h"

	// Minesweeper Class Functions *****************************************************



void Minesweeper::createMinefield(){
	for (int i = 0; i < minefieldRows; i++) {
		vector<bool> row; // Create an empty row
		for (int j = 0; j < minefieldColumns; j++) {
			row.push_back(false); // Add an element (column) to the row
		}
		minefield.push_back(row); // Add the row to the main vector
	}
}

void Minesweeper::createScanfield(){
	for (int i = 0; i < minefieldRows; i++) {
		vector<char> row; // Create an empty row
		for (int j = 0; j < minefieldColumns; j++) {
			row.push_back(' '); // Add an element (column) to the row
		}
		scanfield.push_back(row); // Add the row to the main vector
	}
}

int Minesweeper::fillMinefield(){
	int danger;
	srand((int)time(0));

	for (int i = 0; i < minefieldRows; i++) {
		for (int j = 0; j < minefieldColumns; j++) {
			danger = rand() % (100+1);
			if (danger > 80) {
				mines++;
				minefield[i][j] = true;
			}
		}
	}

	return mines;
}

void Minesweeper::printMinefield(){
	for (int i = 0; i < minefieldRows; i++) {
		for (int k = 0; k < minefieldColumns; k++) {
			cout << "════";
		} cout << "═";

		cout << endl;

		for (int j = 0; j < minefieldColumns; j++) {
			cout << "| ";
			if (minefield[i][j])
				cout << "*";
			else
				cout << " ";

			cout << " ";
			if (j == minefieldColumns - 1)
				cout << "|";

		}
		cout << endl;
		if (i == minefieldRows - 1) {
			for (int k = 0; k < minefieldColumns; k++) {
				cout << "════";
			} cout << "═";
		}
	}
	cout << endl;
}

int Minesweeper::digits(const int& number) {
	if (number > 999)
		return 4;
	else if (number > 99)
		return 3;
	else if (number > 9)
		return 2;
	else if (number >= 0)
		return 1;
	else
		return 0;
}

void Minesweeper::printScanfield(){
	string numspace = "", sepspace = "";
	string header = "";

		// -------* Header *---------
 header = "     ";
	cout << header;

	for (int i = 0; i<minefieldColumns; i++) { //creates column headers
		header = "";
		for (int k = 0; k < ((3) - digits(i+1)); k++) { // adds appropriate whitespace per number
			header.append(" ");
		}
		cout << " " << (i+1) << header;
	}
	cout << endl;

		// End Header

	for (int i = 0; i < minefieldRows; i++) {

		sepspace = "    ";

		if (i == 0) {
			sepspace.append("╔═══");   //handles left side
			for (int k = 1; k < minefieldColumns; k++) {
				sepspace.append("╦═══"); //handles middle part
			}
			cout << sepspace << "╗"; //caps off end
		} else {
			sepspace.append("╠═══");   //handles left side
			for (int k = 1; k < minefieldColumns; k++) {
				sepspace.append("╬═══"); //handles middle part
			}
			cout << sepspace << "╣"; //caps off end
		}
		cout << endl;

		if (digits(i+1) > 1)  // creates uniform row labels
			cout << (i+1) << "  ";
		else
			cout << (i+1) << "   ";


		for (int j = 0; j < minefieldColumns; j++) {
			cout << "║ ";
			cout << scanfield[i][j];
			cout << " ";
			if (j == minefieldColumns - 1)
				cout << "║";

		}
		if (minefieldRows > 7 || minefieldColumns > 7)
			cout << "  " << (i+1) << endl;
		else cout << endl;

		if (i == minefieldRows - 1) {
			sepspace = "    ";
			sepspace.append("╚═══");   //handles left side
			for (int k = 1; k < minefieldColumns; k++) {
				sepspace.append("╩═══"); //handles middle part
			}
			cout << sepspace << "╝"; //caps off end
		}
	}
	cout << endl;

		// Prints bottom numbers if 8 or bigger
	if (minefieldRows > 7 || minefieldColumns > 7) {
		header = "     ";
		cout << header;

		for (int i = 0; i<minefieldColumns; i++) { //creates column headers
			header = "";
			for (int k = 0; k < ((3) - digits(i+1)); k++) { // adds appropriate whitespace per number
				header.append(" ");
			}
			cout << " " << (i+1) << header;
		}
		cout << endl;
	}

}

void Minesweeper::promptUser(){
	bool valid;

	cout << "\nEnter coordinates: [Row] [Column], type \"help\" for command list\n";

	do {
		valid = getInput();
	} while (!valid);


}

void Minesweeper::help(){
	cout << "\nCommand list:\n";
	cout << "Enter two numbers to guess a location\n\tExample: 2 3   (Row 2, Column 3)\n\n";
	cout << "flag: Enter two numbers to flag/unflag a location. A location cannot be triggered while flagged\n\tExample: flag 2 3\tOR\t f 2 3\n\n";
	cout << "mines: Prints out the number of mines on the board. Activated after first guess\n";
	cout << "restart: Clears the board\n";
	cout << "quit: Exits the program\n";
	cout << "help: Brings up this manual\n";
	cout << "hide: Hides this manual\n";
	cout << "credits: Show credits\n";
}

string Minesweeper::tolower(string str) {
	string lowerString = str;

	transform(lowerString.begin(), lowerString.end(), lowerString.begin(), ::tolower);
	return lowerString;
}

bool Minesweeper::getInput(){
	string input1, input2, input3;
	int row, col;
	bool isValid = true;
	bool needMoreArgs;
	needHelp = false;
	showCredits = false;
	printMines = false;

	cin >> input1;

	if (tolower(input1) == "help" || tolower(input1) == "quit" || tolower(input1) == "restart" || tolower(input1) == "mines" || tolower(input1) == "hide" || tolower(input1) == "credits") {
			//if command is a known 1 argument
		needMoreArgs = false;
	} else if ((tolower(input1) != "flag" && tolower(input1) != "f") && !atoi(input1.c_str())) { // everything else except "flag" and numbers command is Invalid
		cout << "Invalid Command\n";
		isValid = false;
		needMoreArgs = false;
	} else {
		restart = false;
		quit = false;
		needMoreArgs = true;
	}


	if (needMoreArgs) { // 2 or more argument commands
		cin >> input2;
		if (tolower(input1) == "flag" || tolower(input1) == "f") {
			cin >> input3;
			row = atoi(input2.c_str());
			col = atoi(input3.c_str());
			if (!(valid(row -1, col - 1))) { //valid takes 0 starting values
				cout << "Please enter values within the board size (" << minefieldRows << "," << minefieldColumns << ")" << endl;
				isValid = false;
			} else flag(row, col);
		}  else { // standard number guess
			row = atoi(input1.c_str());
			col = atoi(input2.c_str());
			if (!(valid(row -1, col - 1))) { //valid takes 0 starting values
				cout << "Please enter values within the board size (" << minefieldRows << "," << minefieldColumns << ")" << endl;
				isValid = false;
			} else if (scanfield[row-1][col-1] != 'F'){ // if its flagged, dont detonate it
				checkguess(row,col); // sends guess starting at 1
			}
		}
	} else if (tolower(input1) == "help") {
		needHelp = true;
	} else if (tolower(input1) == "hide") {
		needHelp = false;
	} else if (tolower(input1) == "mines") {
		printMines = true;
	} else if (tolower(input1) == "restart"){ //restart
		restart = true;
	} else if (tolower(input1) == "quit") { // quit
		quit = true;
	} else if (tolower(input1) == "credits") { // quit
		showCredits = true;
	}


	cin.ignore(INT_MAX,'\n');
	cin.clear();
	return isValid;
}

void Minesweeper::checkguess(const int& y, const int& x){ //changes guess to 0 starting
	srand((int)time(0));
	char mineChar = '0';
	int surroundingMineCount; bool placed;
	const int col = x - 1;
	const int row = y - 1;
	int randcol;
	int randrow;
	int reservedspots;

	if (firstGuess) { // if on first turn make sure its a 0
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (valid(row + i, col + j) && minefield[row + i][col + j]) { // if valid and there is a mine around first guess
					placed = false;
					minefield[row + i][col + j] = false; // remove the bomb
					if (row == 0 || row == minefieldRows - 1 || col == 0 || col == minefieldColumns - 1) { //if its a corner guess
						reservedspots = 4; // only needs 4 spots
					} else reservedspots = 9; // otherwise it needs 9

					if ((minefieldRows * minefieldColumns) - reservedspots >= mines) { //if enough spots to put mines
						while (!placed) { //until its placed
							randcol = rand() % (minefieldColumns);
							randrow = rand() % (minefieldRows);
							if (!minefield[randrow][randcol] && ( (randrow > (row + 1)) || (randrow < (row - 1)) || (randcol > (col + 1)) || (randcol < (col - 1)) ) ) {
								minefield[randrow][randcol] = true;
								placed = true;
							} else placed = false;
						}
					} else mines--; //else not enough spots and remove the mine
				}
			}
		}
		firstGuess = false; //rest of guesses skip this check
	}

	if (minefield[row][col]) {
		showBombs();
		scanfield[row][col] = 'X';
		playing = false;
		win = false;
	} else if (scanfield[row][col] == ' ') { //dont add turns if already guessed there
		if ((surroundingMineCount = surroundingBombs(row,col))){
			mineChar = '0' + surroundingMineCount;
			scanfield[row][col] = mineChar;
		} else {
			scanfield[row][col] = '0';
			revealField(row, col);
		}
		guesses++;
	}

}

int Minesweeper::surroundingBombs(const int& y, const int& x){
	int mines = 0;
	int col, row;
	for (int i = -1; i < 2; i++) {
		row = y + i;
		for (int j = -1; j < 2; j++) {
			col = x + j;
			if (valid(row, col)) {
				if (minefield[row][col]) {
					mines++;
				}
			}
		}
	}
	return mines;
}

void Minesweeper::revealField(const int& y, const int& x) {
	int col, row, mines;
	char mineChar;
	for (int i = -1; i < 2; i++) {
		row = y + i;
		for (int j = -1; j < 2; j++) { // for all boxes surrounding the input location
			col = x + j;
			if (valid(row, col)) { // check within boundaries
				if ((mines = surroundingBombs(row,col))) { // if surrounding bombs, skips already filled spots
					mineChar = '0' + mines;
					scanfield[row][col] = mineChar;
				} else if ((j != 0 || i != 0) && scanfield[row][col] == ' ') { //if not current postion
					scanfield[row][col] = '0';
					revealField(row, col);
				}
			}
		}
	}
}

void Minesweeper::showBombs(){
	for (int i = 0; i < minefieldRows; i++) {
		for (int j = 0; j < minefieldColumns; j++) {
			if (minefield[i][j]) {
				scanfield[i][j] = '*';
			}
		}
	}
}

void Minesweeper::checkwin() {
	int safespots = (minefieldColumns * minefieldRows) - mines;
	int count = 0;
	if (playing) { //dont do anything if already lost
		for (int i = 0; i < minefieldRows; i++) {
			for (int j = 0; j < minefieldColumns; j++) {
				if (scanfield[i][j] != ' ' && scanfield[i][j] != 'F' && scanfield[i][j] != '*' && scanfield[i][j] != 'X') {
						//adds to count for every non untouched space, flag (or bombs if they went off)
					count++;
				}
			}
		}

		if (count == safespots) {
			win = true;
			playing = false;
			showBombs();
		} else win = false;
	}
}

void Minesweeper::flag(const int& y, const int& x) {
	int row = y - 1;
	int col = x - 1;
	static vector<vector<char>> oldVal;

	if (y == -1) { // for game restarting
		oldVal.clear();
	}else if (oldVal.empty()) { //first flag in a game
		for (int i = 0; i < minefieldRows; i++) {
			vector<char> row; // Create an empty row
			for (int j = 0; j < minefieldColumns; j++) {
				row.push_back(' '); // Add an element (column) to the row
			}
			oldVal.push_back(row); // Add the row to the main vector
		}


	}
	if (valid(row, col) && !oldVal.empty()) {
		if (scanfield[row][col] != 'F') {
			oldVal[row][col] = scanfield[row][col];
			scanfield[row][col] = 'F';
			flags++;
		} else {
			scanfield[row][col] = oldVal[row][col];
			flags--;
		}
	}
}

bool Minesweeper::valid(const int& row, const int& col) {
	if ((row >= 0) && (col >= 0) && (row < minefieldRows) && (col < minefieldColumns))
		return true;
	else return false;
}

void Minesweeper::replay () {
	playing = true;
	win = false;
	restart = false;
	needHelp = false;
	firstGuess = false;
	showCredits = false;
	replayed = true;
	scanfield.clear();
	createScanfield();
	guesses = 0;
	flags = 0;
	flag(-1, -1); //resets flag grid
}

void Minesweeper::startGame(int rows = 10, int columns = 10) {
	int mines = 0;
	if (!replayed) { //if its not a replay get new size and bombs
		minefieldRows = rows;
		minefieldColumns = columns;
		do { //makes sure not 0 mines
			clearBoard();
			createMinefield();
			mines = fillMinefield();
		} while (!mines);
	}

	clearscreen();

		//cout << "\nMines: " << mines <<endl << endl; removed due to firstguess policy

	createScanfield();
	time_t start = time(0);

	do {
		if (guesses)
			cout << "Turns: " << guesses << endl << endl;
		printScanfield();
		if (needHelp)
			help();
		if (printMines && firstGuess)
			cout << "\n* Activated after first guess *";
		else if (printMines)
			cout << "\nMines: " << mines << "\tFlags: " << flags << endl;
		if (showCredits) {
			cout << "\nCoded by Justin Oroz\t\t\tjustin.oroz@me.com\n";
		}
		promptUser();
		checkwin();
		clearscreen();
	} while (playing && !quit && !restart);

	if (win) {
		printScanfield();
		cout << "\nYou Win!";
		if (replayed) {
			cout << " (Replayed)";
		}
		cout << "\n" << "Turns: " << guesses << "\t\tTime: " << difftime( time(0), start) << " seconds" << endl;
	} else if (quit) {
		cout << "\nExiting...\n";
	} else if (!restart) {
		printScanfield();
		cout << "\nYou Exploded\n";
	}
	replayed = false; //prepares it for next time
}
