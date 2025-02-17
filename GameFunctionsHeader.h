#pragma once

#include "Main.h"
#include "LinkedListsFunctionsHeader.h"
#include "BoardFunctionsHeader.h"

void Turn(Board board, Player player);
void PlayGame(Board board, Player starting_player);
bool isWinnerFound(Board board, Player* player);
void printTurn(checkersPos* prevPos, checkersPos* newPos);
void updateBiggestnumOfCaptures(int* currNumOfCaptures, int* biggestNumOfCaptures, Player currPlayer, Player* player_with_biggest_num_of_captures);