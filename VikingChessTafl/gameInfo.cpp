/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Konstantin Nikolov
* @idnumber 0MI0600432
* @compiler VC
*
* Common info about pieces and squares
*
*/

#include <iostream>
#include "gameInfo.h"
#include "constants.h"
using namespace std;

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

bool doesSquareExist(int row, int column, int boardSize)
{
	return row >= 0 && row < boardSize && column >= 0 && column < boardSize;
}

bool isPiece(char square)
{
	return square == 'A' || square == 'D' || square == 'K';
}

bool isPlayerPiece(char player, char piece)
{
	return (player == piece) || (player == 'D' && piece == 'K');
}

bool isOtherPlayerPiece(char player, char piece)
{
	return (player == 'A' && piece != 'A') || (player == 'D' && piece != 'D' && piece != 'K');
}

bool isNullOrAttacker(char** board, int row, int column, int boardSize)
{
	if (!doesSquareExist(row, column, boardSize))
	{
		return true;
	}
	return board[row][column] == 'A';
}

bool isKingSurrounded(char** board, int boardSize)
{
	int kingRow = 0, kingColumn = 0;
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (board[i][j] == 'K')
			{
				kingRow = i;
				kingColumn = j;
				break;
			}
		}
	}
	int adjPieces = 0;
	if (isNullOrAttacker(board, kingRow - 1, kingColumn, boardSize))
	{
		adjPieces++;
	}
	if (isNullOrAttacker(board, kingRow + 1, kingColumn, boardSize))
	{
		adjPieces++;
	}
	if (isNullOrAttacker(board, kingRow, kingColumn - 1, boardSize))
	{
		adjPieces++;
	}
	if (isNullOrAttacker(board, kingRow, kingColumn + 1, boardSize))
	{
		adjPieces++;
	}
	return adjPieces == 4;
}

bool hasKingEscaped(char** board, int boardSize)
{
	bool isLeftCorners = board[0][0] == 'K' || board[boardSize - 1][0] == 'K';
	bool isRightCorners = board[0][boardSize - 1] == 'K' || board[boardSize - 1][boardSize - 1] == 'K';
	return isLeftCorners || isRightCorners;
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

void printPieceInfo(int boardSize, char** board)
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
}

void printHelp()
{
	cout << "Possible commands:" << endl;
	cout << "To move a piece, type: move <coords from> <coords to> (example: Move a2 a3)" << endl;
	cout << "To undo a move, type: back" << endl;
	cout << "To see game info, type: info" << endl;
	cout << "To quit the game, type: quit" << endl;
}