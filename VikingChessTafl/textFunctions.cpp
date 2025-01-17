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
* Functions for working with strings
*
*/

#include <iostream>
#include "textFunctions.h"
#include "constants.h"
using namespace std;

bool isDigit(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

bool isSmall(char symbol)
{
	return symbol >= 'a' && symbol <= 'z';
}

bool isCapital(char symbol)
{
	return symbol >= 'A' && symbol <= 'Z';
}

int stringLength(const char* text)
{
	if (text == nullptr)
	{
		return -1;
	}
	int index = 0;
	while (text[index] != '\0')
	{
		index++;
	}
	return index;
}

bool isPrefix(const char* prefix, const char* text)
{
	if (prefix == nullptr || text == nullptr)
	{
		cout << "Invalid argument!" << endl;
		return false;
	}
	while (*prefix != '\0')
	{
		if (*prefix != *text)
		{
			return false;
		}
		prefix++;
		text++;
	}
	return true;
}

bool areEqual(const char* text1, const char* text2)
{
	if (text1 == nullptr || text2 == nullptr)
	{
		cout << "Invalid argument!" << endl;
		return false;
	}
	bool areEqualLengths = stringLength(text1) == stringLength(text2);
	return isPrefix(text1, text2) && areEqualLengths;
}

void lower(char* text)
{
	if (text == nullptr)
	{
		cout << "Invalid argument!" << endl;
		return;
	}
	while (*text != '\0')
	{
		if (isCapital(*text))
		{
			*text = *text + TO_LOWER;
		}
		text++;
	}
}

int indexOf(const char* text, char symbol)
{
	if (text == nullptr)
	{
		cout << "Invalid argument!" << endl;
		return -1;
	}
	int index = 0;
	while (*text != '\0')
	{
		if (*text == symbol)
		{
			return index;
		}
		index++;
		text++;
	}
	return -1;
}