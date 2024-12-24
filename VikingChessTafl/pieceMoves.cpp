#include <iostream>
#include "pieceMoves.h"
#include "textFunctions.h"
using namespace std;

const int MOVE_COMMAND_LENGTH = 10;
const char TO_LETTER = 'a';
const char TO_NUMBER = '0';

bool isValidHorCoord(char coord, int boardSize)
{
	return coord >= TO_LETTER && coord <= boardSize + TO_LETTER - 1;
}

bool isValidVertCoord(int coord, int boardSize)
{
	return coord >= 1 && coord <= boardSize;
}

bool isValidMove(char* command, int boardSize)
{
	if (command == nullptr)
	{
		return false;
	}
	return false;
}