#pragma once

#include "Main.h"

//branch 2
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
SingleSourceMovesList* FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* source, unsigned int* height);
SingleSourceMovesList* compareTreeHeights(unsigned int heightL, unsigned int heightR, unsigned int* height, SingleSourceMovesList* leftList, SingleSourceMovesList* rightList, SingleSourceMovesTreeNode* source);
SingleSourceMovesList* compareNumofCaptures(SingleSourceMovesList* leftList, SingleSourceMovesList* rightList, unsigned int heightL, unsigned int heightR, unsigned int* height, SingleSourceMovesTreeNode* source);
SingleSourceMovesList* compareColNumberForPlayerB(SingleSourceMovesList* leftList, SingleSourceMovesList* rightList, unsigned int heightL, unsigned int heightR, unsigned int* height, SingleSourceMovesTreeNode* source);
SingleSourceMovesList* compareColNumberForPlayerT(SingleSourceMovesList* leftList, SingleSourceMovesList* rightList, unsigned int heightL, unsigned int heightR, unsigned int* height, SingleSourceMovesTreeNode* source);
SingleSourceMovesList* makeEmptySingleSourceMovesList();
void checkAllocSingleSourceMovesList(SingleSourceMovesList* pnode);
void checkAllocSingleSourceMovesListCell(SingleSourceMovesListCell* pnode);
bool isEmptySingleSourceMovesList(SingleSourceMovesList* list);
SingleSourceMovesListCell* createNewSingleSourceMovesListCell(checkersPos* position, unsigned short captures);
void insertDataToStartSingleSourceMovesList(SingleSourceMovesList* list, checkersPos* position, unsigned short captures);
void insertCellToStartSingleSourceMovesList(SingleSourceMovesList* list, SingleSourceMovesListCell* newHead);
void freeSingleSourceMovesList(SingleSourceMovesList* list);
void freeSingleSourceMovesListRec(SingleSourceMovesListCell* head);

//branch 3
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);
void freeMultipleSourceMovesListCellRec(MultipleSourceMovesListCell* head);
void freeMultipleSourceMovesList(MultipleSourceMovesList* ptr);
MultipleSourceMovesListCell* createMultipleSourceMovesListCell(SingleSourceMovesList* data, MultipleSourceMovesListCell* next);
void insertDataToEndMultipleSourceMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* data);
void insertNodeToEndMultipleSourceMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* newTail);
void checkAllocMultipleSourceMovesListCell(MultipleSourceMovesListCell* ptr);
MultipleSourceMovesList* createMultipleSourceMovesList();
void checkAllocMultipleSourceMovesList(MultipleSourceMovesList* list);
void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList* list);
bool isEmptyMultipleSourceMovesList(MultipleSourceMovesList* list);

//branch 4

MultipleSourceMovesListCell* getBestSquareToMoveFrom(Player player, MultipleSourceMovesListCell* best_square_to_move_from, MultipleSourceMovesListCell* current);
MultipleSourceMovesListCell* getBestSquareToMoveFromForTPlayer(Player player, MultipleSourceMovesListCell* best_square_to_move_from, MultipleSourceMovesListCell* current);
MultipleSourceMovesListCell* getBestSquareToMoveFromForBPlayer(Player player, MultipleSourceMovesListCell* best_square_to_move_from, MultipleSourceMovesListCell* current);