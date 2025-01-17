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
* Declarations for move and piece capture functionality
*
*/

#pragma once
#define pieceMoves

bool isValidMoveFormat(const char* command, int boardSize);
bool tryMove(char player, const char* command, char** board, int boardSize, int moveCoords[4]);
void analyzeForTakenPieces(char player, char** board, int boardSize, int endRow, int endColumn, bool comment);
void movePiece(char** board, bool isKingFromCenterMove, int startRow, int startColumn, int endRow, int endColumn);