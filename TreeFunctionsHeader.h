#pragma once
#include "Main.h"
SingleSourceMovesTree* CreateNewSingleSourceMovesTree(Board board);
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);
SingleSourceMovesTree* FindSingleSourceMovesForPlayer(Board board, Player p, checkersPos* src);
void checkIfAllocTreeSucceded(SingleSourceMovesTree* ptr);
void checkIfAllocTreeNodeSucceded(SingleSourceMovesTreeNode* ptr);
void checkIfAllocCheckersPosSucceded(checkersPos* ptr);
SingleSourceMovesTreeNode* BuildTreeForPlayerHelper(Board b, checkersPos* src, Player p, int newRow, int newCol, int opponentRow, int opponentCol,
	int capturesSoFar, int movesToGo, int capturedDuringMove);
SingleSourceMovesTreeNode* initSingleSingleSourceMovesTreeNode(Board b, int newRow, int newCol, int opponentRow, int opponentCol, int capturesSoFar);
SingleSourceMovesTreeNode* BuildTreeForPlayer(Board board, checkersPos* src, Player p, SingleSourceMovesTreeNode* root);
bool canYouSkipLeft(SingleSourceMovesTreeNode* root, checkersPos* src, int movesToGo, int capturedDuringMove, Player p);
bool canYouSkipRight(SingleSourceMovesTreeNode* root, checkersPos* src, int movesToGo, int capturedDuringMove, Player p);
//branch 2
void freeTree(SingleSourceMovesTree* tr);
void freeTreeRec(SingleSourceMovesTreeNode* source);

