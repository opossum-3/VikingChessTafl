#include <iostream>
#include "textFunctions.h"
using namespace std;

const char TO_LOWER = 'a' - 'A';
const char TO_DIGIT = '0';

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

int occurrenceCount(const char* text, char symbol)
{
	if (text == nullptr)
	{
		cout << "Invalid argument!" << endl;
		return -1;
	}
	int count = 0;
	while (*text != '\0')
	{
		if (*text == symbol)
		{
			count++;
		}
		text++;
	}
	return count;
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

int parseInt(const char* text)
{
	if (text == nullptr)
	{
		cout << "Invalid argument!" << endl;
		return -1;
	}
	int result = 0;
	while (*text != '\0')
	{
		if (isDigit(*text) == false)
		{
			return -1;
		}
		int digit = *text - TO_DIGIT;
		result *= 10;
		result += digit;
		text++;
	}
	return result;
}