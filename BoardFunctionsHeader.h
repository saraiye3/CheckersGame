#pragma once

#include "Main.h"

void PrintBoard(Board b);
void InitBoard(Board board);
void ChangePlayerPos(Board b, Player p, checkersPos* oldPos, checkersPos* newPos);
void SwitchPlayer(Player* player);
void DuplicateBoard(Board dest, Board src);
void DeleteOpponentFromBoard(Board board, Player player, checkersPos* prevPos, checkersPos* nextPos);
void DeleteOpponentFromPos(Board b, int row, int col);
bool CheckIfInBorder(int row, int col);
bool CheckIfSquareIsFree(Board b, int row, int col);
unsigned int countNumOfPawns(Board board, Player player);
bool checkIfPlayerIsAtLastLineOfOpponent(Player* winner, Board board);
bool checkIfPlayerHasNoPawnsLeft(Board board, Player* winner);