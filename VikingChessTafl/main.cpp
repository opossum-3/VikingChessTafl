#include <iostream>
#include "startBoard.h"
#include "pieceMoves.h"
#include "textFunctions.h"
#include "constants.h"
using namespace std;

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
		case SMALL_BOARD_SIZE:
			return SMALL_BOARD_PIECE_COUNT;
		case MEDIUM_BOARD_SIZE:
			return MEDIUM_BOARD_PIECE_COUNT;
		case LARGE_BOARD_SIZE:
			return LARGE_BOARD_PIECE_COUNT;
		default:
			break;
	}
	return -1;
}

struct moveInfo
{
	int startRow, startColumn;
	int endRow, endColumn;
	moveInfo* previous;
	moveInfo* next;
};

int moveCount(moveInfo** moveState)
{
	moveInfo* current = *moveState;
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

void recordMove(moveInfo** move, int moveCoords[4])
{
	moveInfo* newMove = new moveInfo();
	newMove->startRow = moveCoords[0];
	newMove->startColumn = moveCoords[1];
	newMove->endRow = moveCoords[2];
	newMove->endColumn = moveCoords[3];
	newMove->next = nullptr;
	if (*move == nullptr)
	{
		*move = newMove;
	}
	else
	{
		moveInfo* moveValue = *move;
		while (moveValue->next != nullptr)
		{
			moveValue = moveValue->next;
		}
		newMove->previous = moveValue;
		moveValue->next = newMove;
	}
}

char** undoMove(char** board, int boardSize, moveInfo** move)
{
	for (int i = 0; i < boardSize; i++)
	{
		delete[] board[i];
	}
	delete[] board;
	board = getBoard(boardSize);
	moveInfo* moveValue = *move;
	int turnIndex = 0;
	while (moveValue->next != nullptr)
	{
		turnIndex++;
		moveValue = moveValue->next;
	}
	moveValue = *move;
	for (int i = 0; i < turnIndex; i++)
	{
		int startRow = moveValue->startRow;
		int startColumn = moveValue->startColumn;
		int endRow = moveValue->endRow;
		int endColumn = moveValue->endColumn;
		char player = (i % 2 == 0) ? 'A' : 'D';
		bool isKing = (board[startRow][startColumn] == 'K');
		bool isFromCenter = (startRow == boardSize / 2) && (startColumn == boardSize / 2);
		movePiece(board, (isKing && isFromCenter), startRow, startColumn, endRow, endColumn);
		analyzeForTakenPieces(player, board, boardSize, endRow, endColumn, false);
		moveValue = moveValue->next;
	}
	if (moveValue->previous != nullptr)
	{
		moveValue->previous->next = nullptr;
		delete moveValue;
		moveValue = nullptr;
	}
	else
	{
		delete* move;
		*move = nullptr;
	}
	return board;
}

char** turn(char player, char** board, int boardSize, moveInfo** state, bool& hasMoved)
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
	moveInfo** initialState = new moveInfo*[1];
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