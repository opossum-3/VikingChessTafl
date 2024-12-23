#include <iostream>
#include "startBoard.h"
using namespace std;

void clearConsole() {
	cout << "\033[;H"; // Moves cursor to the top left
	cout << "\033[J"; // Clears the console
}

int handleInput()
{
	char input;
	cin >> input;
	switch (input)
	{
		case 's':
			clearConsole();
			break;
		case 'q':
			clearConsole();
			cout << "Quitting..." << endl;
			break;
		default:
			cout << "Invalid input!" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return 1;
	}
	return 0;
}

int main()
{
	cout << "Tafl - Viking chess" << endl;
	cout << endl;
	do
	{
		cout << "Type (s) to start" << endl;
		cout << "Type (q) to quit" << endl;
		cout << endl;
	} while (handleInput());
	int boardSize = chooseBoardSize();
	char** board = getBoard(boardSize);
	printBoard(board, boardSize);
}