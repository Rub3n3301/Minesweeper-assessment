//made by Ruben Sailer. minesweeper assessment

#include <iostream> 
#include <conio.h> 

#include <fstream>//used for acessing text files in the meu options
#include <string>//allows use of getline

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
	}
};


void playGame() {
	
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