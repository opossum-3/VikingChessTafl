#include <iostream>
#include "pieceMoves.h"
#include "textFunctions.h"
using namespace std;

const int MOVE_COMMAND_LENGTH = 10;
const char TO_LETTER = 'a';
const char TO_DIGIT = '0';

bool isValidHorCoord(char coord, int boardSize)
{
	return coord >= TO_LETTER && coord <= boardSize + TO_LETTER - 1;
}

bool isValidVertCoord(int coord, int boardSize)
{
	return coord >= 1 && coord <= boardSize;
}

bool isValidCoord(const char* text, int endIndex, int boardSize)
{
	if (text == nullptr)
	{
		return false;
	}
	if (isValidHorCoord(*text, boardSize) == false)
	{
		return false;
	}
	text++;
	endIndex--;
	int coord = 0;
	for (int i = 0; i <= endIndex; i++)
	{
		if (isDigit(text[i]))
		{
			coord *= 10;
			coord += (text[i] - TO_DIGIT);
		}
		else
		{
			return false;
		}
	}
	return isValidVertCoord(coord, boardSize) && endIndex >= 0;
}

bool isValidMoveFormat(const char* command, int boardSize)
{
	if (command == nullptr)
	{
		return false;
	}
	int length = stringLength(command);
	int minLength = stringLength("move a2 a3");
	int maxLength = stringLength("move a10 a11");
	if (length > maxLength || length < minLength)
	{
		return false;
	}
	command += stringLength("move ");
	int spaceIndex = indexOf(command, ' ');
	if (spaceIndex < 1)
	{
		return false;
	}
	bool isValidFirst = isValidCoord(command, spaceIndex - 1, boardSize);
	command += spaceIndex + 1;
	bool isValidSecond = isValidCoord(command, stringLength(command) - 1, boardSize);
	return isValidFirst && isValidSecond;
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

bool isHorVertMove(int startRow, int startColumn, int endRow, int endColumn)
{
	if (startRow != endRow && startColumn != endColumn)
	{
		return false;
	}
	if (startRow == endRow && startColumn == endColumn)
	{
		return false;
	}
	return true;
}

bool isMovingThroughPieces(char** board, int startRow, int endRow, int startColumn, int endColumn)
{
	if (startRow == endRow)
	{
		int min = startColumn < endColumn ? startColumn : endColumn;
		int max = startColumn > endColumn ? startColumn : endColumn;
		for (int i = min + 1; i < max; i++)
		{
			char squareSymbol = board[startRow][i];
			if (squareSymbol != ' ' && squareSymbol != 'X')
			{
				return true;
			}
		}
	}
	if (startColumn == endColumn)
	{
		int min = startRow < endRow ? startRow : endRow;
		int max = startRow > endRow ? startRow : endRow;
		for (int i = min + 1; i < max; i++)
		{
			char squareSymbol = board[i][startColumn];
			if (squareSymbol != ' ' && squareSymbol != 'X')
			{
				return true;
			}
		}
	}
	return false;
}

bool isValidMove(char player, char** board, int startRow, int startColumn, int endRow, int endColumn)
{
	char startCell = board[startRow][startColumn];
	char endCell = board[endRow][endColumn];
	if (isOtherPlayerPiece(player, startCell))
	{
		cout << "You can't move other player's pieces or empty squares." << endl;
		return false;
	}
	if (isHorVertMove(startRow, startColumn, endRow, endColumn) == false)
	{
		cout << "You can only move horizontally or vertically in a straight line." << endl;
		return false;
	}
	if (endCell == 'X' && startCell != 'K')
	{
		cout << "Only defender's king can step on \'X\' squares." << endl;
		return false;
	}
	if (endCell == 'A' || endCell == 'D' || endCell == 'K')
	{
		cout << "You can't step on other pieces." << endl;
		return false;
	}
	if (isMovingThroughPieces(board, startRow, endRow, startColumn, endColumn))
	{
		cout << "You can't move through other pieces." << endl;
		return false;
	}
	return true;
}

void movePiece(char** board, bool isKingFromCenterMove, int startRow, int startColumn, int endRow, int endColumn)
{
	char piece = board[startRow][startColumn];
	board[endRow][endColumn] = piece;
	board[startRow][startColumn] = isKingFromCenterMove ? 'X' : ' ';
}

void takePiece(char** board, int row, int column)
{
	char piece = board[row][column];
	board[row][column] = ' ';
	cout << ((piece == 'A') ? "An attacker's " : "A defender's ") << "piece has been captured." << endl;
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

void analyzeForTakenAt(char player, char** board, int boardSize, int row, int column, int vertDir, int horDir)
{
	bool squareExists = doesSquareExist(row + vertDir, column + horDir, boardSize);
	if (!(squareExists && isPiece(board[row + vertDir][column + horDir])))
	{
		return;
	}
	bool isEnemyPiece = isOtherPlayerPiece(player, board[row + vertDir][column + horDir]);
	if (isEnemyPiece && board[row + vertDir][column + horDir] != 'K')
	{
		if (!doesSquareExist(row + 2 * vertDir, column + 2 * horDir, boardSize))
		{
			return;
		}
		bool isX = board[row + 2 * vertDir][column + 2 * horDir] == 'X';
		bool samePlayerPiece = isPlayerPiece(player, board[row + 2 * vertDir][column + 2 * horDir]);
		if (board[row + vertDir][column + horDir] != 'K' && (isX || samePlayerPiece))
		{
			takePiece(board, row + vertDir, column + horDir);
		}
	}
}

void analyzeForTakenPieces(char player, char** board, int boardSize, int endRow, int endColumn)
{
	analyzeForTakenAt(player, board, boardSize, endRow, endColumn, -1, 0);
	analyzeForTakenAt(player, board, boardSize, endRow, endColumn, 0, -1);
	analyzeForTakenAt(player, board, boardSize, endRow, endColumn, 1, 0);
	analyzeForTakenAt(player, board, boardSize, endRow, endColumn, 0, 1);
}

bool tryMove(char player, const char* command, char** board, int boardSize)
{
	if (command == nullptr)
	{
		return false;
	}
	command += stringLength("move ");
	int startColumn = *command - TO_LETTER;
	command++;
	int startRow = 0;
	while (isDigit(*command))
	{
		startRow *= 10;
		startRow += ((*command) - TO_DIGIT);
		command++;
	}
	startRow = boardSize - startRow;
	command++;
	int endColumn = *command - TO_LETTER;
	command++;
	int endRow = 0;
	while (isDigit(*command))
	{
		endRow *= 10;
		endRow += ((*command) - TO_DIGIT);
		command++;
	}
	endRow = boardSize - endRow;
	if (isValidMove(player, board, startRow, startColumn, endRow, endColumn))
	{
		bool isKing = (board[startRow][startColumn] == 'K');
		bool isFromCenter = (startRow == boardSize / 2) && (startColumn == boardSize / 2);
		movePiece(board, (isKing && isFromCenter), startRow, startColumn, endRow, endColumn);
		analyzeForTakenPieces(player, board, boardSize, endRow, endColumn);
		return true;
	}
	else
	{
		return false;
	}
}