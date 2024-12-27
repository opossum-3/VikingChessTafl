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

struct boardState
{
	int startRow, startColumn;
	int endRow, endColumn;
	boardState* previous;
	boardState* next;
};

void recordMove(boardState** lastMove, int moveCoords[4])
{
	boardState* newMove = new boardState();
	newMove->startRow = moveCoords[0];
	newMove->startColumn = moveCoords[1];
	newMove->endRow = moveCoords[2];
	newMove->endColumn = moveCoords[3];
	newMove->next = nullptr;
	if (*lastMove == nullptr)
	{
		*lastMove = newMove;
	}
	else
	{
		newMove->previous = *lastMove;
		(*lastMove)->next = newMove;
	}
}

bool undoMove(char** board, int boardSize, boardState** state)
{
	if (*state == nullptr)
	{
		return false;
	}
	for (int i = 0; i < boardSize; i++)
	{
		delete[] board[i];
	}
	delete[] board;
	board = getBoard(boardSize);
	boardState* copy = *state;
	int turnIndex = 0;
	while (copy->next != nullptr)
	{
		turnIndex++;
		copy = copy->next;
	}
	for (int i = 0; i < turnIndex; i++)
	{
		int startRow = (*state)->startRow;
		int startColumn = (*state)->startColumn;
		int endRow = (*state)->endRow;
		int endColumn = (*state)->endColumn;
		char player = (i % 2 == 0) ? 'A' : 'D';
		bool isKing = (board[startRow][startColumn] == 'K');
		bool isFromCenter = (startRow == boardSize / 2) && (startColumn == boardSize / 2);
		movePiece(board, (isKing && isFromCenter), startRow, startColumn, endRow, endColumn);
		analyzeForTakenPieces(player, board, boardSize, endRow, endColumn, false);
		*state = (*state)->next;
	}
	delete[] *state;
	*state = nullptr;
	return true;
}

bool turn(char player, char** board, int boardSize, boardState** state)
{
	while (true)
	{
		char input[BUFFER_SIZE] = {};
		cin.getline(input, BUFFER_SIZE);
		lower(input);
		if (isPrefix("move ", input) && isValidMoveFormat(input, boardSize))
		{
			cout << "Moving..." << endl;
			int moveCoords[4] = { -1, -1, -1, -1 };
			if (tryMove(player, input, board, boardSize, moveCoords))
			{
				recordMove(state, moveCoords);
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
		else if (areEqual("back", input))
		{
			if (undoMove(board, boardSize, state))
			{
				cout << endl;
				printBoard(board, boardSize);
				if (player == 'A')
				{
					player = 'D';
				}
				else
				{
					player = 'A';
				}
				return true;
			}
			else
			{
				cout << "You can't undo moves at initial position." << endl;
			}
			//cout << endl << ((player == 'A') ? "Attacker's" : "Defender's") << " turn:" << endl;
		}
		else if (areEqual("help", input))
		{
			cout << "Possible commands:" << endl;
			cout << "To move a piece, type: move <coords from> <coords to> (example: Move a2 a3)" << endl;
			cout << "To undo a move, type: back" << endl;
			cout << "To see game info, type: info" << endl;
			cout << "To quit the game, type: quit" << endl;
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
	boardState** initialState = new boardState*[1];
	initialState[0] = nullptr;
	printBoard(board, boardSize);
	clearInputBuffer();
	char player = 'A';
	while (true)
	{
		if (player == 'A')
		{
			cout << "Attacker's turn:" << endl;
			if (!turn(player, board, boardSize, initialState))
			{
				// Player quit
				break;
			}
			player = 'D';
		}
		else if (player == 'D')
		{
			cout << "Defender's turn:" << endl;
			if (!turn(player, board, boardSize, initialState))
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