#include <iostream>
#include "textFunctions.h"
using namespace std;

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