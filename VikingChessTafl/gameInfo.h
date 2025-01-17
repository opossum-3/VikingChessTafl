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
* Declaration of functions for common info about pieces and squares
*
*/

#pragma once

int attackersAtStart(int boardSize);
int attackerPieceCount(char** board, int boardSize);
int defenderPieceCount(char** board, int boardSize);
bool doesSquareExist(int row, int column, int boardSize);
bool isPiece(char square);
bool isPlayerPiece(char player, char piece);
bool isOtherPlayerPiece(char player, char piece);
bool isNullOrAttacker(char** board, int row, int column, int boardSize);
bool isKingSurrounded(char** board, int boardSize);
bool hasKingEscaped(char** board, int boardSize);
bool isGameOver(char** board, int boardSize);
void printPieceInfo(int boardSize, char** board);
void printHelp();