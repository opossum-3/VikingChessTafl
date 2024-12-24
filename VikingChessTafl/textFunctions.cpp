#include <iostream>
#include "textFunctions.h"
using namespace std;

int stringLength(char* text)
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

bool isPrefix(char* prefix, char* text)
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