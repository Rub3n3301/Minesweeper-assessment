//made by Ruben Sailer. minesweeper assessment

#include <iostream> 
#include <conio.h> 

#include <fstream>//used for acessing text files in the meu options
#include <string>//allows use of getline and to_string conversion
#include <stdlib.h>//used in the random number generator
#include <time.h>//used as a seed for the random number generator


using namespace std;

const int boardWidth = 3;
const int boardHeight = 3;
bool cheatsActivated = true;

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
		displayValue = " ";
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

	bool checkSquare() {
		
		if (displayValue == "F") {
			cout << "this square is flagged. if you want to check it you must flag it again to remove the flag\n";
			return false;
		}
		if (isRevealed == true) {
			cout << "this square already revealed\n";
			return false;
		}

		isRevealed = true;
		displayValue = trueValue;
		if (isBomb == true) {
			return true;
		}
		else {
			return false;
		}
	}

	void flagSquare() {
		if (!isRevealed) {
			if (displayValue == "F") {
				displayValue = " ";
			}
			else {
				displayValue = "F";
			}
		}
		else {
			cout << "this square has already been revealed. Too late to flag it!\n";
		}
	}

	bool stateSquare() {
		if (isBomb == true) {
			if (displayValue == "F") {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (displayValue == "F") {
				return false;
			}
			else if (isRevealed == true) {
				return true;
			}
			else {
				return false;
			}
		}
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
					gridPoints[x][y].trueValue = '0' + sumOfSurroundingBombs;
				}
			}
		}

	}

	string printGrid() {

		string boardImage = "";

		boardImage += "    ";//making space for the side header

		for (int x = 0; x < boardWidth; x++) {//print the top header
			boardImage += "[ ";
			boardImage += ((char)(x + 65) );
			boardImage += " ]";

		}
		boardImage += "\n";//next line
		boardImage += "\n";//next line

		for (int r = 0; r < boardHeight; r++) {//does each row of the board
			boardImage += "[";
			boardImage += to_string(r);
			boardImage += "] ";//side header

			for (int c = 0; c < boardWidth; c++) {
				boardImage += "[ " + gridPoints[c][r].displayValue + " ]";
			}
			boardImage += "\n";
		}
		return boardImage;
	}

	string printTrueGrid() {
		string boardImage = "";

		boardImage += "    ";//making space for the side header

		for (int x = 0; x < boardWidth; x++) {//print the top header
			boardImage += "[ ";
			boardImage += ((char)(x + 65));
			boardImage += " ]";

		}
		boardImage += "\n";//next line
		boardImage += "\n";//next line

		for (int r = 0; r < boardHeight; r++) {//does each row of the board
			boardImage += "[";
			boardImage += to_string(r);
			boardImage += "] ";//side header

			for (int c = 0; c < boardWidth; c++) {
				boardImage += "[ " + gridPoints[c][r].trueValue + " ]";
			}
			boardImage += "\n";
		}
		return boardImage;
	}

	bool modifyGrid(string input) {
		bool gameOver = false;

		char command = input[0];
		char xPositionInput = input[1];
		char yPositionInput = input[2];

		int xPos = ((int)xPositionInput) - 65;
		int yPos;
		if (isdigit(yPositionInput)) {
			yPos = yPositionInput - '0';
		}
		else {
			cout << "you need to enter a number for the y position\n";
			return 0;
		}

		if (!(0 < xPos < boardWidth)) {
			cout << "you need to enter a coordinate within the grid for the x axis\n";
			return 0;
		}
		if (!(0 < yPos < boardHeight)) {
			cout << "you need to enter a coordinate within the grid for the y axis\n";
			return 0;
		}

		if (command == '?') {
			gameOver = gridPoints[xPos][yPos].checkSquare();
		}
		else if (command == '!') {
			gridPoints[xPos][yPos].flagSquare();
		}

		if (gameOver) {
			return true;
		}
		else {
			return false;
		}
	}

	bool gameWonGrid() {
		for (int x = 0; x < boardWidth; x++) {
			for (int y = 0; y < boardHeight; y++) {
				
				if (gridPoints[x][y].stateSquare() == false) {
					return false;
				}
			
			}
		}
		return true;
	}
};

void playGame() {

	bool gameOver = false;
	bool gameWon = false;
	grid theBoard = grid();

	string display = theBoard.printGrid();
	//cout << display << "\n";

	theBoard.initialiseGrid(3);

	display = theBoard.printGrid();
	cout << display << "\n";

	string move;
	int turnCount = 0;
	while (gameOver == false && gameWon == false) {
		turnCount += 1;
		
		cout << "make your move!\n";
		cout << "turn count = " << turnCount << "\n";
		cin >> move;
		system("CLS");//ooo system is bad

		gameOver = theBoard.modifyGrid(move);

		cout << "this is the updated grid\n";
		display = theBoard.printGrid();
		cout << display << "\n";

		if (cheatsActivated) {
			cout << "this is the cheater grid -- Cheats are on!\n";
			display = theBoard.printTrueGrid();
			cout << display << "\n";
		}

		gameWon = theBoard.gameWonGrid();

	}

	if (gameWon == true) {
		system("CLS");//ooo system is bad
		cout << "WELL DONE!\n";
		display = theBoard.printTrueGrid();
		cout << display << "\n";
		cout << "you have won the game :))\n";
		cout << "you won in " << turnCount << " moves\n";
	}

	if (gameOver == true) {
		system("CLS");//ooo system is bad
		cout << "BOOM!\n";
		display = theBoard.printTrueGrid();
		cout << display << "\n";
		cout << "you have lost the game :((\n";
		cout << "you survived " << turnCount << " moves\n";
	}

	cout << "--------------------------\n";
	cout << "press enter and you will returned to the main menu\n";
	_getch();
}

void menu() {
	menuOption options[] = { menuOption("MenuOptions//playGame.txt"), menuOption("MenuOptions//settings.txt"), menuOption("MenuOptions//credits.txt") };
	for (int x = 0; x < *(&options + 1) - options; x++) {
		options[x].displayOption();
		cout << "============================================================================\n";
	}
	char choice;
	cin >> choice;

	string cheating = " ";
	switch (choice) {
	case 'p':
		playGame();
		break;
	case 'c':
		cout << "this game was made by ruben sailer\n";
		cout << "created in 2021\n";
		cout << "he hopes you enjoy it!\n";
		_getch();
		break;
	case 's':
		cout << "do you wants cheats on?\n";
		
		while (cheating != "y" && cheating != "n") {
			cout << "y for yes. n for no\n";
			cin >> cheating;
		}
		if (cheating == "y") {
			cheatsActivated = true;
			cout << "cheats activated!\n";
		}
		else if (cheating == "n") {
			cheatsActivated = false;
			cout << "cheats removed!\n";
		}
		break;

	default:
		cout << "you need to enter a valid tag!\n";
		_getch();
		break;
	}
	system("CLS");
	menu();
}

int main(){
	menu();


}