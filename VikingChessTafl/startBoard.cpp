#include <iostream>
#include "startBoard.h"
using namespace std;

const int CELL_WIDTH = 6;
const int CELL_HEIGHT = 4;

char** getBoard(int N)
{
	char** board = new char* [N + 1];
	for (int i = 0; i < N; i++)
	{
		char* row = new char[N + 1];
		for (int j = 0; j < N; j++)
		{
			row[j] = ' ';
		}
		row[N] = '\0';
		board[i] = row;
	}
	board[N] = nullptr;
	board[0][0] = 'K';
	board[0][1] = 'A';
	board[0][2] = 'D';
	return board;
}

void drawPieceImage(char** boardImage, int row, int column, char piece)
{
	switch (piece)
	{
		case 'A':
			boardImage[row][column - 1] = piece;
			boardImage[row][column + 1] = piece;
			boardImage[row + 1][column + 2] = piece;
			boardImage[row + 1][column - 2] = piece;
			boardImage[row][column] = piece;
			boardImage[row - 1][column] = piece;
			break;
		case 'D':
			boardImage[row - 1][column - 1] = piece;
			boardImage[row - 1][column] = piece;
			boardImage[row][column - 1] = piece;
			boardImage[row][column + 1] = piece;
			boardImage[row + 1][column - 1] = piece;
			boardImage[row + 1][column] = piece;
			break;
		case 'K':
			boardImage[row - 1][column - 1] = piece;
			boardImage[row][column - 1] = piece;
			boardImage[row + 1][column - 1] = piece;
			boardImage[row][column] = piece;
			boardImage[row - 1][column + 1] = piece;
			boardImage[row + 1][column + 1] = piece;
			break;
		default:
			break;
	}
}

void drawPieces(char** board, char** boardImage, int boardSize)
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			int height = i * CELL_HEIGHT + CELL_HEIGHT / 2;
			int width = j * CELL_WIDTH + CELL_WIDTH / 2;
			drawPieceImage(boardImage, height, width, board[i][j]);
		}
	}
}

char** getBoardImage(char** board, int boardSize)
{
	int pieceRow = 0, pieceColumn = 0;
	int tableWidth = 6 * boardSize + 1;
	int tableHeight = 4 * boardSize + 1;
	char** boardImage = new char* [tableHeight + 1];
	for (int i = 0; i < tableHeight; i++)
	{
		char* row = new char[tableWidth + 1];
		for (int j = 0; j < tableWidth; j++)
		{
			if (i % 4 == 0)
			{
				row[j] = '-';
			}
			else
			{
				if (j % 6 == 0)
				{
					row[j] = '|';
				}
				else
				{
					row[j] = ' ';
				}
			}
		}
		row[tableWidth] = '\0';
		boardImage[i] = row;
	}
	boardImage[tableHeight] = nullptr;
	drawPieces(board, boardImage, boardSize);
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