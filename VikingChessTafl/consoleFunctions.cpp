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
* Functions for clearing the input buffer and console
*
*/

#include <iostream>
#include "consoleFunctions.h"
using namespace std;

void clearConsole()
{
	cout << "\033[;H"; // Moves cursor to the top left
	cout << "\033[J"; // Clears the console
}

void clearInputBuffer()
{
	cin.clear();	// Clears error flags from the cin
	cin.sync();		// Discards unread characters from the input buffer
	cin.ignore();	// Discards characters from the input buffer
}