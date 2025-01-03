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

int attackerPieceCount(char** board, int boardSize)
{
	int count = 0;
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (board[i][j] == 'A')
			{
				count++;
			}
		}
	}
	return count;
}

int defenderPieceCount(char** board, int boardSize)
{
	int count = 0;
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (board[i][j] == 'D' || board[i][j] == 'K')
			{
				count++;
			}
		}
	}
	return count;
}

int attackersAtStart(int boardSize)
{
	switch (boardSize)
	{
		case 9:
			return 16;
		case 11:
			return 24;
		case 13:
			return 32;
		default:
			break;
	}
	return -1;
}

struct boardState
{
	int startRow, startColumn;
	int endRow, endColumn;
	boardState* previous;
	boardState* next;
};

int moveCount(boardState** state)
{
	boardState* current = *state;
	if (current == nullptr)
	{
		return 0;
	}
	int count = 1;
	while (current->next != nullptr)
	{
		current = current->next;
		count++;
	}
	return count;
}

void recordMove(boardState** state, int moveCoords[4])
{
	boardState* newMove = new boardState();
	newMove->startRow = moveCoords[0];
	newMove->startColumn = moveCoords[1];
	newMove->endRow = moveCoords[2];
	newMove->endColumn = moveCoords[3];
	newMove->next = nullptr;
	if (*state == nullptr)
	{
		*state = newMove;
	}
	else
	{
		boardState* copy = *state;
		while (copy->next != nullptr)
		{
			copy = copy->next;
		}
		newMove->previous = copy;
		copy->next = newMove;
	}
}

char** undoMove(char** board, int boardSize, boardState** state)
{
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
	copy = *state;
	for (int i = 0; i < turnIndex; i++)
	{
		int startRow = copy->startRow;
		int startColumn = copy->startColumn;
		int endRow = copy->endRow;
		int endColumn = copy->endColumn;
		char player = (i % 2 == 0) ? 'A' : 'D';
		bool isKing = (board[startRow][startColumn] == 'K');
		bool isFromCenter = (startRow == boardSize / 2) && (startColumn == boardSize / 2);
		movePiece(board, (isKing && isFromCenter), startRow, startColumn, endRow, endColumn);
		analyzeForTakenPieces(player, board, boardSize, endRow, endColumn, false);
		copy = copy->next;
	}
	if (copy->previous != nullptr)
	{
		copy->previous->next = nullptr;
		delete copy;
		copy = nullptr;
	}
	else
	{
		delete* state;
		*state = nullptr;
	}
	return board;
}

char** turn(char player, char** board, int boardSize, boardState** state, bool& hasMoved)
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
				hasMoved = true;
				return board;
			}
			cout << "Please try again." << endl;
		}
		else if (areEqual("quit", input))
		{
			cout << "Game quit" << endl;
			hasMoved = false;
			return board;
		}
		else if (areEqual("back", input))
		{
			if (*state == nullptr)
			{
				cout << "You can't undo moves at initial position." << endl;
			}
			else
			{
				board = undoMove(board, boardSize, state);
				printBoard(board, boardSize);
				player = (player == 'A') ? 'D' : 'A';
				hasMoved = true;
				return board;
			}
		}
		else if (areEqual("info", input))
		{
			int initialAttackers = attackersAtStart(boardSize);
			int initialDefenders = initialAttackers / 2 + 1;
			int attackers = attackerPieceCount(board, boardSize);
			int defenders = defenderPieceCount(board, boardSize);
			cout << "There are " << attackers << " attackers on the board." << endl;
			cout << "There are " << defenders << " defenders on the board";
			cout << " (including the king)." << endl;
			cout << "A total of " << initialAttackers - attackers << " attackers have been taken." << endl;
			cout << "A total of " << initialDefenders - defenders << " defenders have been taken." << endl;
			int moves = moveCount(state);
			if (moves == 0)
			{
				cout << "No moves have been made yet." << endl;
			}
			else
			{
				cout << "Attackers have made " << moves / 2 + (moves % 2) << " moves." << endl;
				cout << "Defenders have made " << moves / 2 << " moves." << endl;
			}
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
		bool hasMoved = false;
		bool& hasMovedRef = hasMoved;
		if (player == 'A')
		{
			cout << "Attacker's turn:" << endl;
			board = turn(player, board, boardSize, initialState, hasMovedRef);
			if (!hasMovedRef)
			{
				// Player quit
				break;
			}
			player = 'D';
		}
		else if (player == 'D')
		{
			cout << "Defender's turn:" << endl;
			board = turn(player, board, boardSize, initialState, hasMovedRef);
			if (!hasMovedRef)
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