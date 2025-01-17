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
* Declaration for functions for working with strings
*
*/

#pragma once
#define textFunctions

int stringLength(const char* text);
bool isPrefix(const char* prefix, const char* text);
bool areEqual(const char* text1, const char* text2);
void lower(char* text);
bool isDigit(char symbol);
bool isSmall(char symbol);
int indexOf(const char* text, char symbol);