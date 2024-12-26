#include <iostream>
#include "startBoard.h"
#include "pieceMoves.h"
#include "textFunctions.h"
using namespace std;

const int BUFFER_SIZE = 50;

void clearConsole()
{
	cout << "\033[;H"; // Moves cursor to the top left
	cout << "\033[J"; // Clears the console
}

void clearInputBuffer()
{
	cin.clear();	// Clears error flags from the cin
	cin.sync();		// Discards unread characters from the input buffer
	cin.ignore();	// Discards characters from the input buffer
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

bool turn(char player, char** board, int boardSize)
{
	while (true)
	{
		char input[BUFFER_SIZE] = {};
		cin.getline(input, BUFFER_SIZE);
		lower(input);
		if (isPrefix("move ", input) && isValidMoveFormat(input, boardSize))
		{
			cout << "Moving..." << endl;
			if (tryMove(player, input, board, boardSize))
			{
				cout << endl;
				printBoard(board, boardSize);
				return true;
			}
			cout << "Please try again." << endl;
		}
		else if (areEqual("quit", input))
		{
			cout << "Game quit" << endl;
			return false;
		}
		else
		{
			cout << "Incorrect command. Please try again." << endl;
		}
	}
}

bool isGameOver(char** board, int boardSize)
{
	if (isKingSurrounded(board, boardSize))
	{
		cout << "The king is surrounded. Attackers win!" << endl;
		return true;
	}
	if (hasKingEscaped(board, boardSize))
	{
		cout << "The king has escaped. Defenders win!" << endl;
		return true;
	}
	return false;
}

void startGame()
{
	int boardSize = chooseBoardSize();
	char** board = getBoard(boardSize);
	printBoard(board, boardSize);
	clearInputBuffer();
	char player = 'A';
	while (true)
	{
		if (player == 'A')
		{
			cout << "Attacker's turn:" << endl;
			if (!turn(player, board, boardSize))
			{
				// Player quit
				break;
			}
			player = 'D';
		}
		else if (player == 'D')
		{
			cout << "Defender's turn:" << endl;
			if (!turn(player, board, boardSize))
			{
				// Player quit
				break;
			}
			player = 'A';
		}
		if (isGameOver(board, boardSize))
		{
			cout << "Game over." << endl;
			break;
		}
	}
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