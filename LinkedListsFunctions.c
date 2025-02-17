#include "Main.h"
#include "LinkedListsFunctionsHeader.h"
#include "TreeFunctionsHeader.h"

//branch 2

/*This function gets a tree of possible moves
and returns a list representing the most optimal move the player can make*/

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	SingleSourceMovesList* mostOptimalMovesList;
	unsigned int height = 0;

	//if the tree is empty or there are no possible moves
	if (moves_tree == NULL || moves_tree->source == NULL || (moves_tree->source->next_move[0] == NULL && moves_tree->source->next_move[1] == NULL))
		mostOptimalMovesList = NULL;
	else
		mostOptimalMovesList = FindSingleSourceOptimalMoveHelper(moves_tree->source, &height);

	freeTree(moves_tree);
	return mostOptimalMovesList;
}

SingleSourceMovesList* FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* source, unsigned int* height)
{
	SingleSourceMovesList* res, * leftList, * rightList;
	unsigned int heightL, heightR;

	if (source->next_move[0] == NULL && source->next_move[1] == NULL) //if is a leaf
	{
		res = makeEmptySingleSourceMovesList();
		insertDataToStartSingleSourceMovesList(res, source->pos, source->total_captures_so_far);
		*height = 0;
	}
	else if (source->next_move[0] == NULL)
	{
		//call with the right side of the tree
		rightList = FindSingleSourceOptimalMoveHelper(source->next_move[1], &heightR);
		*height = heightR + 1; //add one for the source
		//insert source to the end of the right list
		insertDataToStartSingleSourceMovesList(rightList, source->pos, source->total_captures_so_far);
		res = rightList;
	}
	else if (source->next_move[1] == NULL)
	{
		//call with the left side of the tree
		leftList = FindSingleSourceOptimalMoveHelper(source->next_move[0], &heightL);
		*height = heightL + 1; //add one for the source
		//insert source to the end of the left list
		insertDataToStartSingleSourceMovesList(leftList, source->pos, source->total_captures_so_far);
		res = leftList;
	}
	else
	{
		leftList = FindSingleSourceOptimalMoveHelper(source->next_move[0], &heightL);
		rightList = FindSingleSourceOptimalMoveHelper(source->next_move[1], &heightR);
		heightL++; //add one for the source
		heightR++; //add one for the source

		//find and return the list representing the most optimal path
		res = compareTreeHeights(heightL, heightR, height, leftList, rightList, source);
	}
	return res;
}


SingleSourceMovesList* compareTreeHeights(unsigned int heightL, unsigned int heightR, unsigned int* height, SingleSourceMovesList* leftList, SingleSourceMovesList* rightList, SingleSourceMovesTreeNode* source) //compare two paths and return the most optimal one
{
	SingleSourceMovesList* res;

	if (heightL > heightR) //if the left path has more captures
	{
		*height = heightL;
		//add source to the start of the most optimal list
		insertDataToStartSingleSourceMovesList(leftList, source->pos, source->total_captures_so_far); //alternative: insertDataToStartList(res, source->pos, captures>1 ? 1 : source->captures);
		freeSingleSourceMovesList(rightList);  //free the less optimal list
		res = leftList;
	}
	else if (heightR > heightL) //if the right path has more captures
	{
		*height = heightR;
		insertDataToStartSingleSourceMovesList(rightList, source->pos, source->total_captures_so_far); //add source to the start of the most optimal list
		freeSingleSourceMovesList(leftList);  //free the less optimal list
		res = rightList;
	}
	else //if (heightL == heightR) 
	{
		//check if they have the same number of captures
		res = compareNumofCaptures(leftList, rightList, heightL, heightR, height, source);
	}
	return res;
}

SingleSourceMovesList* compareNumofCaptures(SingleSourceMovesList* leftList, SingleSourceMovesList* rightList, unsigned int heightL, unsigned int heightR, unsigned int* height, SingleSourceMovesTreeNode* source) //compare number of captures so far between two tree nodes
{
	SingleSourceMovesList* res;

	//if the left path contains more captures - return the left list
	if (leftList->tail->captures > rightList->tail->captures)
	{
		*height = heightL;
		freeSingleSourceMovesList(rightList);
		insertDataToStartSingleSourceMovesList(leftList, source->pos, source->total_captures_so_far);
		res = leftList;
	}
	//if the right path contains more captures - return the right list
	else if (rightList->tail->captures > leftList->tail->captures)
	{
		*height = heightR;
		freeSingleSourceMovesList(leftList);
		insertDataToStartSingleSourceMovesList(rightList, source->pos, source->total_captures_so_far);
		res = rightList;
	}
	else //if both paths contain the same number of captures - compare number of column
	{
		checkersPos* position = source->pos;

		if (source->board[position->row][position->col] == PLAYER_B)
			res = compareColNumberForPlayerB(leftList, rightList, heightL, heightR, height, source);
		else //if the player is T
			res = compareColNumberForPlayerT(leftList, rightList, heightL, heightR, height, source);
	}

	return res;
}

SingleSourceMovesList* compareColNumberForPlayerB(SingleSourceMovesList* leftList, SingleSourceMovesList* rightList, unsigned int heightL, unsigned int heightR, unsigned int* height, SingleSourceMovesTreeNode* source) //compare column number of two tree nodes
{
	SingleSourceMovesList* res;

	//if in the end of the left path B would be standing in a smaller column than in the end of the right path
	if (leftList->tail->position->col < rightList->tail->position->col)
	{
		*height = heightL;
		freeSingleSourceMovesList(rightList);
		insertDataToStartSingleSourceMovesList(leftList, source->pos, source->total_captures_so_far);
		res = leftList;
	}
	else
	{
		*height = heightR;
		freeSingleSourceMovesList(leftList);
		insertDataToStartSingleSourceMovesList(rightList, source->pos, source->total_captures_so_far);
		res = rightList;
	}

	return res;
}

SingleSourceMovesList* compareColNumberForPlayerT(SingleSourceMovesList* leftList, SingleSourceMovesList* rightList, unsigned int heightL, unsigned int heightR, unsigned int* height, SingleSourceMovesTreeNode* source) //compare column number of two tree nodes
{
	SingleSourceMovesList* res;

	//if in the end of the left path T would be standing in a bigger column than in the end of the right path
	if (leftList->tail->position->col > rightList->tail->position->col)
	{
		*height = heightL;
		freeSingleSourceMovesList(rightList);
		insertDataToStartSingleSourceMovesList(leftList, source->pos, source->total_captures_so_far);
		res = leftList;
	}
	else
	{
		*height = heightR;
		freeSingleSourceMovesList(leftList);
		insertDataToStartSingleSourceMovesList(rightList, source->pos, source->total_captures_so_far);
		res = rightList;
	}

	return res;
}

SingleSourceMovesList* makeEmptySingleSourceMovesList()
{
	SingleSourceMovesList* res;
	res = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkAllocSingleSourceMovesList(res);
	res->head = res->tail = NULL;

	return res;
}

void checkAllocSingleSourceMovesList(SingleSourceMovesList* pnode)
{
	if (pnode == NULL)
	{
		printf("Memory allocation failed!!!\n");
		exit(1);
	}
}

void checkAllocSingleSourceMovesListCell(SingleSourceMovesListCell* pnode)
{
	if (pnode == NULL)
	{
		printf("Memory allocation failed!!!\n");
		exit(1);
	}
}

bool isEmptySingleSourceMovesList(SingleSourceMovesList* list)
{
	return (list->head == NULL);
}

SingleSourceMovesListCell* createNewSingleSourceMovesListCell(checkersPos* position, unsigned short captures)
{
	SingleSourceMovesListCell* newListCell;
	newListCell = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkAllocSingleSourceMovesListCell(newListCell);
	checkersPos* newPosition = (checkersPos*)malloc(sizeof(checkersPos));
	checkIfAllocCheckersPosSucceded(newPosition);

	newPosition->row = position->row;
	newPosition->col = position->col;
	newListCell->position = newPosition;
	newListCell->captures = captures;
	newListCell->next = NULL;

	return newListCell;
}

void insertDataToStartSingleSourceMovesList(SingleSourceMovesList* list, checkersPos* position, unsigned short captures)
{
	SingleSourceMovesListCell* newListCell = NULL;

	newListCell = createNewSingleSourceMovesListCell(position, captures);
	insertCellToStartSingleSourceMovesList(list, newListCell);
}

void insertCellToStartSingleSourceMovesList(SingleSourceMovesList* list, SingleSourceMovesListCell* newHead)
{
	if (isEmptySingleSourceMovesList(list))
	{
		list->head = newHead;
		list->tail = newHead;
	}
	else
	{
		newHead->next = list->head;
		list->head = newHead;
	}
}

void freeSingleSourceMovesList(SingleSourceMovesList* list) //free list of moves
{
	if (list == NULL)
		return;
	freeSingleSourceMovesListRec(list->head);
	free(list);
}

void freeSingleSourceMovesListRec(SingleSourceMovesListCell* head) //free list of moves
{
	if (head != NULL)
	{
		freeSingleSourceMovesListRec(head->next);
		free(head->position);
		free(head);
	}
}

//branch 3

void freeMultipleSourceMovesList(MultipleSourceMovesList* ptr) {
	if (ptr == NULL)
		return;
	if (ptr->head != NULL) {
		freeMultipleSourceMovesListCellRec(ptr->head);
	}
	free(ptr);
}

void freeMultipleSourceMovesListCellRec(MultipleSourceMovesListCell* head) {
	if (head != NULL) {
		freeSingleSourceMovesList(head->single_source_moves_list);
		freeMultipleSourceMovesListCellRec(head->next);
	}
	free(head);
}

/*This function calculates all possible moves for a given player on a game board.
It iterates through each square occupied by the player and generates a tree of all possible moves from that square.
The function then selects the best move from each square and adds it to a list of best moves.
Finally, it returns the list of all possible moves for the player.*/
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player) {
	unsigned int i, j;
	MultipleSourceMovesList* myMultipleSourceMovesList = createMultipleSourceMovesList();
	makeEmptyMultipleSourceMovesList(myMultipleSourceMovesList);
	SingleSourceMovesTree* moves_tree;
	SingleSourceMovesList* best_move;
	checkersPos* checkerPos = (checkersPos*)malloc(sizeof(checkersPos));
	checkIfAllocCheckersPosSucceded(checkerPos);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == player)
			{
				checkerPos->row = i;
				checkerPos->col = j;
				//get tree of all possible moves to make from current square
				moves_tree = FindSingleSourceMoves(board, checkerPos);
				//get the best move to make from current square
				best_move = FindSingleSourceOptimalMove(moves_tree);
				if (best_move != NULL)
					//add the best move from current square to the list of best moves
					insertDataToEndMultipleSourceMovesList(myMultipleSourceMovesList, best_move);
			}
		}
	}
	free(checkerPos);
	return myMultipleSourceMovesList;
}
MultipleSourceMovesListCell* createMultipleSourceMovesListCell(SingleSourceMovesList* data, MultipleSourceMovesListCell* next) {
	MultipleSourceMovesListCell* res;
	res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	checkAllocMultipleSourceMovesListCell(res);
	res->single_source_moves_list = data;
	res->next = next;
	return res;
}
void checkAllocMultipleSourceMovesListCell(MultipleSourceMovesListCell* ptr) {
	if (ptr == NULL) {
		printf("memory allocation failed. program exiting\n");
		exit(1);
	}
}
void insertDataToEndMultipleSourceMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* data) {
	MultipleSourceMovesListCell* newTail;
	newTail = createMultipleSourceMovesListCell(data, NULL);
	insertNodeToEndMultipleSourceMovesList(lst, newTail);
}

void insertNodeToEndMultipleSourceMovesList(MultipleSourceMovesList* list, MultipleSourceMovesListCell* newTail)
{
	if (isEmptyMultipleSourceMovesList(list))
		list->head = list->tail = newTail;
	else
	{
		list->tail->next = newTail;
		list->tail = newTail;
	}
}

MultipleSourceMovesList* createMultipleSourceMovesList()
{
	MultipleSourceMovesList* list;

	list = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	checkAllocMultipleSourceMovesList(list);

	return list;
}

void checkAllocMultipleSourceMovesList(MultipleSourceMovesList* list)
{
	if (list == NULL)
	{
		printf("Memory allocation failed!!!\n");
		exit(1);
	}
}

void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList* list)
{
	list->head = list->tail = NULL;
}

bool isEmptyMultipleSourceMovesList(MultipleSourceMovesList* list)
{
	return (list->head == NULL);
}

MultipleSourceMovesListCell* getBestSquareToMoveFromForTPlayer(Player player, MultipleSourceMovesListCell* best_square_to_move_from, MultipleSourceMovesListCell* current) {
	if (current->single_source_moves_list->head->position->row > best_square_to_move_from->single_source_moves_list->head->position->row)
	{
		return current;
	}
	else if (current->single_source_moves_list->head->position->row == best_square_to_move_from->single_source_moves_list->head->position->row)
	{
		if (current->single_source_moves_list->head->position->col > best_square_to_move_from->single_source_moves_list->head->position->col)
		{
			return current;
		}
		else
		{
			return best_square_to_move_from;
		}
	}
	else
	{
		return best_square_to_move_from;
	}
}
MultipleSourceMovesListCell* getBestSquareToMoveFromForBPlayer(Player player, MultipleSourceMovesListCell* best_square_to_move_from, MultipleSourceMovesListCell* current) {
	if (best_square_to_move_from->single_source_moves_list->head->position->row < current->single_source_moves_list->head->position->row)
	{
		return best_square_to_move_from;
	}
	else if (current->single_source_moves_list->head->position->row == best_square_to_move_from->single_source_moves_list->head->position->row)
	{
		if (best_square_to_move_from->single_source_moves_list->head->position->col < current->single_source_moves_list->head->position->col)
		{
			return best_square_to_move_from;
		}
		else
		{
			return current;
		}
	}
	else
	{
		return current;
	}
}
/*This function gets a list of paths from different squares
and returns the best square to move from*/
MultipleSourceMovesListCell* getBestSquareToMoveFrom(Player player, MultipleSourceMovesListCell* best_square_to_move_from, MultipleSourceMovesListCell* current)
{
	if (player == PLAYER_T)
	{
		return getBestSquareToMoveFromForTPlayer(player, best_square_to_move_from, current);
	}
	if (player == PLAYER_B)
	{
		return getBestSquareToMoveFromForBPlayer(player, best_square_to_move_from, current);
	}
}