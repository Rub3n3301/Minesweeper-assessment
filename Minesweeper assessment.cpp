//made by Ruben Sailer. minesweeper assessment

#include <iostream> 
#include <conio.h> 

#include <fstream>//used for acessing text files in the meu options
#include <string>//allows use of getline
#include <stdlib.h>//used in the random number generator
#include <time.h>//used as a seed for the random number generator

using namespace std;

const int boardWidth = 10;
const int boardHeight = 10;

class menuOption {
public:
	char optionTag = '*';
	string optionName = "<EMPTY>";
	string optionDescription = "this menu option is not availible yet";

	menuOption(string path) {

		ifstream file(path);

		if (file.good()) {
			string lineInfo;
			getline(file, lineInfo);
			//cout << lineInfo << endl;
			//cout << lineInfo.at(0) << endl;
			optionTag = lineInfo.at(0);

			getline(file, lineInfo);
			//cout << lineInfo << endl;
			optionName = lineInfo;

			getline(file, lineInfo);
			//cout << lineInfo << endl;
			optionDescription = lineInfo;
			file.close();
		}
		else {
			cout << "file for " << path << " was not found\n";
		}
	}

	void displayOption() {
		cout << "for " << optionName << " press: " << optionTag << "\n";
		cout << optionDescription << "\n";
	}
};

class gridSquare {
public:
	bool isBomb= false;
	bool isRevealed= false;
	string trueValue="";
	string displayValue = "";

	gridSquare() {
		isBomb = false;
		isRevealed = false;
		trueValue = "";
		displayValue = "";
	}

	void initialiseSquare(bool bomb) {
		if (bomb == true) {
			isBomb = true;
			trueValue = 'B';

		}
		else {
			trueValue = ' ';
		}
		displayValue = 'X';
	}
};

class grid {
public:
	gridSquare gridPoints[boardWidth][boardHeight];

	grid() {
		for (int x = 0; x < boardWidth; x++) {
			for (int y = 0; y < boardHeight; y++) {
				gridPoints[x][y] = gridSquare();
			}
		}
	}
	void initialiseGrid(int numberOfBombs) {
		for (int x = 0; x < boardWidth; x++) {
			for (int y = 0; y < boardHeight; y++) {
				gridPoints[x][y].initialiseSquare(false);
			}
		}
		// set all board peices to be empty

		int bombsPlaced = 0;
		srand(time(NULL)); //initialize the random seed

		while (bombsPlaced < numberOfBombs) {
			int randXIndex = rand() % boardWidth; //generates a random number between 0 and boardwidth-1
			int randYIndex = rand() % boardHeight; //generates a random number between 0 and boardheight-1
			if (gridPoints[randXIndex][randYIndex].isBomb == false) {
				gridPoints[randXIndex][randYIndex].initialiseSquare(true);
				bombsPlaced += 1;
			}
		}
		//add the bombs

		for (int x = 0; x < boardWidth; x++) {
			for (int y = 0; y < boardHeight; y++) {
				int sumOfSurroundingBombs = 0;//for each peice on the board, count the number of surrounding bombs

				if (gridPoints[x][y].isBomb == true) {
					
				}
				else {
					for (int n = x - 1; n <= x + 1; n++) {

						if (n < 0 || n > boardWidth - 1) {
							
						}
						else {
							for (int z = y - 1; z <= y + 1; z++) {
								if (z < 0 || z > boardHeight - 1) {
									
								}
								else {
									if (gridPoints[n][z].isBomb == true) {
										sumOfSurroundingBombs += 1;
									}
								}
							}
						}
					}
					gridPoints[x][y].trueValue = sumOfSurroundingBombs;// maybe problems here?
				}

			}
		}


	}
	string printGrid() {
		string boardImage = "";

		boardImage += "   ";//making space for the side header

		for (int x = 0; x < boardWidth; x++) {//print the top header
			boardImage += "[";
			boardImage += ((char)(x + 25) );
			boardImage += "]";

		}
		boardImage += "\n";//next line

		for (int r = 0; r < boardHeight; r++) {//does each row of the board
			boardImage += "[";
			boardImage += r;
			boardImage += "]";//side header

			for (int c = 0; c < boardWidth; c++) {
				boardImage += "[" + gridPoints[c][r].displayValue + "]";
			}
			boardImage += "\n";
		}
		return boardImage;
	}//or here?
};

void playGame() {
	grid theBoard = grid();
	theBoard.initialiseGrid(10);
	string display = theBoard.printGrid();
	cout << display;
}

void menu() {
	menuOption options[] = { menuOption("MenuOptions//playGame.txt"), menuOption("MenuOptions//settings.txt"), menuOption("MenuOptions//credits.txt") };
	for (int x = 0; x < *(&options + 1) - options; x++) {
		options[x].displayOption();
	}
	char choice;
	cin >> choice;
	switch (choice) {
	case 'p':
		playGame();
	}
}

int main(){
	menu();


}