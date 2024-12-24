#include <iostream>
#include "startBoard.h"
using namespace std;

const int CELL_WIDTH = 6;
const int CELL_HEIGHT = 4;

void positionDefenders(char** board, int boardSize)
{
	int center = boardSize / 2;
	int padding = boardSize == 13 ? 3 : 2;
	for (int i = -padding; i <= padding; i++)
	{
		if (i == 0)
		{
			continue;
		}
		board[center][center + i] = 'D';
		board[center + i][center] = 'D';
	}
	if (boardSize > 9) 
	{
		board[center - 1][center - 1] = 'D';
		board[center - 1][center + 1] = 'D';
		board[center + 1][center - 1] = 'D';
		board[center + 1][center + 1] = 'D';
	}
}

void positionAttackers(char** board, int boardSize)
{
	int center = boardSize / 2;
	int padding = 1;
	switch (boardSize)
	{
		case 9:
			padding = 1;
			break;
		case 11:
			padding = 2;
			break;
		case 13:
			padding = 3;
			break;
		default:
			break;
	}
	for (int i = -padding; i <= padding; i++)
	{
		board[center + i][0] = 'A';
		board[0][center + i] = 'A';
		board[center + i][boardSize - 1] = 'A';
		board[boardSize - 1][center + i] = 'A';
	}
	board[center][1] = 'A';
	board[1][center] = 'A';
	board[center][boardSize - 2] = 'A';
	board[boardSize - 2][center] = 'A';
}

void positionPieces(char** board, int boardSize)
{
	int center = boardSize / 2;
	board[center][center] = 'K';
	positionDefenders(board, boardSize);
	positionAttackers(board, boardSize);
}

char** getBoard(int boardSize)
{
	char** board = new char* [boardSize + 1];
	for (int i = 0; i < boardSize; i++)
	{
		char* row = new char[boardSize + 1];
		for (int j = 0; j < boardSize; j++)
		{
			row[j] = ' ';
		}
		row[boardSize] = '\0';
		board[i] = row;
	}
	board[boardSize] = nullptr;
	board[0][0] = 'X';
	board[0][boardSize - 1] = 'X';
	board[boardSize - 1][0] = 'X';
	board[boardSize - 1][boardSize - 1] = 'X';
	positionPieces(board, boardSize);
	return board;
}

void drawSymbolImage(char** boardImage, int row, int column, char symbol)
{
	switch (symbol)
	{
		case 'A':
			boardImage[row][column - 1] = symbol;
			boardImage[row][column + 1] = symbol;
			boardImage[row + 1][column + 2] = symbol;
			boardImage[row + 1][column - 2] = symbol;
			boardImage[row][column] = symbol;
			boardImage[row - 1][column] = symbol;
			break;
		case 'D':
			boardImage[row - 1][column - 1] = symbol;
			boardImage[row - 1][column] = symbol;
			boardImage[row][column - 1] = symbol;
			boardImage[row][column + 1] = symbol;
			boardImage[row + 1][column - 1] = symbol;
			boardImage[row + 1][column] = symbol;
			break;
		case 'K':
			boardImage[row - 1][column - 1] = symbol;
			boardImage[row][column - 1] = symbol;
			boardImage[row + 1][column - 1] = symbol;
			boardImage[row][column] = symbol;
			boardImage[row - 1][column + 1] = symbol;
			boardImage[row + 1][column + 1] = symbol;
			break;
		case 'X':
			boardImage[row - 1][column - 2] = symbol;
			boardImage[row - 1][column + 2] = symbol;
			boardImage[row][column] = symbol;
			boardImage[row + 1][column - 2] = symbol;
			boardImage[row + 1][column + 2] = symbol;
			break;
		default:
			break;
	}
}

void drawSymbols(char** board, char** boardImage, int boardSize)
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			int vertPosition = i * CELL_HEIGHT + CELL_HEIGHT / 2;
			int horPosition = j * CELL_WIDTH + CELL_WIDTH / 2;
			drawSymbolImage(boardImage, vertPosition, horPosition, board[i][j]);
		}
	}
}

char** getBoardImage(char** board, int boardSize)
{
	int pieceRow = 0, pieceColumn = 0;
	int tableWidth = CELL_WIDTH * boardSize + 1;
	int tableHeight = CELL_HEIGHT * boardSize + 1;
	char** boardImage = new char* [tableHeight + 1];
	for (int i = 0; i < tableHeight; i++)
	{
		char* row = new char[tableWidth + 1];
		for (int j = 0; j < tableWidth; j++)
		{
			if (i % CELL_HEIGHT == 0)
			{
				row[j] = '-';
			}
			else
			{
				row[j] = (j % CELL_WIDTH == 0) ? '|' : ' ';
			}
		}
		row[tableWidth] = '\0';
		boardImage[i] = row;
	}
	boardImage[tableHeight] = nullptr;
	drawSymbols(board, boardImage, boardSize);
	return boardImage;
}

void printBoard(char** board, int boardSize)
{
	char** image = getBoardImage(board, boardSize);
	int index = 0;
	while (image[index] != nullptr)
	{
		cout << image[index] << endl;
		index++;
	}
	for (int i = 0; i < boardSize; i++)
	{
		delete[boardSize + 1] image[i];
	}
	delete[boardSize + 1] image;
}

int chooseBoardSize()
{
	int boardSize = 0;
	while (true)
	{
		cout << "Board size NxN, input N (9, 11 or 13):" << endl;
		cin >> boardSize;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (boardSize == 9  || boardSize == 11 || boardSize == 13)
		{
			cout << "Board size " << boardSize << "x" << boardSize << " chosen" << endl;
			break;
		}
		cout << "Invalid input!" << endl;
	}
	return boardSize;
}