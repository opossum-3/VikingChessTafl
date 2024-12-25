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
			coord += (text[i] - TO_NUMBER);
		}
		else
		{
			return false;
		}
	}
	return isValidVertCoord(coord, boardSize) && endIndex >= 0;
}

bool isValidMoveFormat(char* command, int boardSize)
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