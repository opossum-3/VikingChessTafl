#include <iostream>
#include "startBoard.h"
using namespace std;

void clearConsole() {
	cout << "\033[;H"; // Moves cursor to the top left
	cout << "\033[J"; // Clears the console
}

int startInput()
{
	char input;
	cin >> input;
	switch (input)
	{
		case 's':
			clearConsole();
			cout << "Game started" << endl;
			return 1;
		case 'q':
			clearConsole();
			cout << "Game quit" << endl;
			return 0;
		default:
			cout << "Invalid input!" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return -1;
	}
	return 0;
}

void startGame()
{
	int boardSize = chooseBoardSize();
	char** board = getBoard(boardSize);
	printBoard(board, boardSize);
}

int main()
{
	cout << "Tafl - Viking chess" << endl;
	cout << endl;
	while (true)
	{
		cout << "Type (s) to start" << endl;
		cout << "Type (q) to quit" << endl;
		cout << endl;
		int inputResult = startInput();
		if (inputResult == 1)
		{
			startGame();
			break;
		}
		else if (inputResult == 0)
		{
			break;
		}
	}
}