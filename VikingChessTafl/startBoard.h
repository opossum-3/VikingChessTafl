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
* Declaration for board setup at the start of the game
*
*/

#pragma once
#define startBoard

char** getBoard(int boardSize);
int chooseBoardSize();
void printBoard(char** board, int boardSize);