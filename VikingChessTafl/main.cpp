#include <iostream>
#include "startBoard.h"
#include "textFunctions.h"
using namespace std;

const int BUFFER_SIZE = 50;

void clearConsole() {
	cout << "\033[;H"; // Moves cursor to the top left
	cout << "\033[J"; // Clears the console
}

int startInput()
{
	char input[BUFFER_SIZE] = {};
	cin.getline(input, BUFFER_SIZE);
	if (areEqual(input, "start"))
	{
		clearConsole();
		cout << "Game started" << endl;
		return 1;
	}
	if (areEqual(input, "quit"))
	{
		clearConsole();
		cout << "Game quit" << endl;
		return 0;
	}
	cout << "Invalid input!" << endl;
	return -1;
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
		cout << "Type \"start\" to start a new game" << endl;
		cout << "Type \"quit\" to exit the game" << endl;
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