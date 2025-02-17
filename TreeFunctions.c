#include "Main.h"
#include "TreeFunctionsHeader.h"
#include "BoardFunctionsHeader.h"
//#include "LinkedListsFunctionsHeader.h"

/*
	check if allocation of tree succeded
*/
void checkIfAllocTreeSucceded(SingleSourceMovesTree* ptr) {
	if (ptr == NULL) {
		printf("memory allocation failed");
		exit(1);
	}
}
//check if allocation of tree node succeded
void checkIfAllocTreeNodeSucceded(SingleSourceMovesTreeNode* ptr) {
	if (ptr == NULL) {
		printf("memory allocation failed");
		exit(1);
	}
}
//check if allocation of checker pos instance succeded
void checkIfAllocCheckersPosSucceded(checkersPos* ptr) {
	if (ptr == NULL) {
		printf("memory allocation failed");
		exit(1);
	}
}
//branch1
/*
	build moes tree based on current board status
	params:
	board - game's board
	src - player's stating position
	return SingleSourceMovesTree pointer to instance in heap
*/
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {
	if (board[src->row][src->col] == ' ') {
		return NULL;
	}
	else {
		if (board[src->row][src->col] == PLAYER_B) {
			return FindSingleSourceMovesForPlayer(board, PLAYER_B, src);
		}
		else {
			return FindSingleSourceMovesForPlayer(board, PLAYER_T, src);
		}
	}
}
/*
	auxilary function for FindSingleSourceMoves tree
	params:
	board - game's board
	p - the player which has the turn
	src - player's position
	return SingleSourceMovesTree pointer to instance in heap
*/
SingleSourceMovesTree* FindSingleSourceMovesForPlayer(Board board, Player p, checkersPos* src) {
	SingleSourceMovesTree* singleSourceMovesTree = CreateNewSingleSourceMovesTree(board);
	singleSourceMovesTree->source = BuildTreeForPlayer(board, src, p, singleSourceMovesTree->source);

	return singleSourceMovesTree;
}
/*
	auxilary function for FindSingleSourceMovesForPlayer
	found SingleSourceMoves , so lets build its tree
*/
SingleSourceMovesTreeNode* BuildTreeForPlayer(Board board, checkersPos* src, Player p, SingleSourceMovesTreeNode* root) {
	root = BuildTreeForPlayerHelper(board, src, p, src->row, src->col, DONT_HAVE_AN_OPPENENT_TO_DELETE, DONT_HAVE_AN_OPPENENT_TO_DELETE, 0, 1, 0);
	return root;
}
/*
* check if player can capture to left
*	params:
*	root - root of Single Source Moves Tree
*	src - players starting position
*	movesToGo - how many step the player can make during current branch in tree
*	capturedDuringMove - num of catures has already made in current branch in tree
*	p - current player
*/
bool canYouSkipLeft(SingleSourceMovesTreeNode* root, checkersPos* src, int movesToGo, int capturedDuringMove, Player p) {
	if (movesToGo < 1 && capturedDuringMove == 0) {
		return false;
	}
	if (p == PLAYER_B) {
		if ((root->board)[(root->pos->row) - 1][(root->pos->col) - 1] == PLAYER_T) {
			if (CheckIfInBorder((root->pos->row) - 2, (root->pos->col) - 2) == true) {
				if (CheckIfSquareIsFree(root->board, (root->pos->row) - 2, (root->pos->col) - 2) == true) {
					return true;
				}
			}
		}
	}
	else if (p == PLAYER_T) {
		if ((root->board)[(root->pos->row) + 1][(root->pos->col) - 1] == PLAYER_B) {
			if (CheckIfInBorder((root->pos->row) + 2, (root->pos->col) - 2) == true) {
				if (CheckIfSquareIsFree(root->board, (root->pos->row) + 2, (root->pos->col) - 2) == true) {
					return true;
				}
			}
		}
	}
	return false;
}
/*check if players can make a capture to the right
*	root - root of Single Source Moves Tree
*	src - players starting position
*	movesToGo - how many step the player can make during current branch in tree
*	capturedDuringMove - num of catures has already made in current branch in tree
*	p - current player
*/
bool canYouSkipRight(SingleSourceMovesTreeNode* root, checkersPos* src, int movesToGo, int capturedDuringMove, Player p) {
	if (movesToGo < 1 && capturedDuringMove == 0) {
		return false;
	}
	if (p == PLAYER_B) {
		if ((root->board)[(root->pos->row) - 1][(root->pos->col) + 1] == PLAYER_T) {
			if (CheckIfInBorder((root->pos->row) - 2, (root->pos->col) + 2) == true) {
				if (CheckIfSquareIsFree(root->board, (root->pos->row) - 2, (root->pos->col) + 2) == true) {
					return true;
				}
			}
		}
	}
	else if (p == PLAYER_T) {
		if ((root->board)[(root->pos->row) + 1][(root->pos->col) + 1] == PLAYER_B) {
			if (CheckIfInBorder((root->pos->row) + 2, (root->pos->col) + 2) == true) {
				if (CheckIfSquareIsFree(root->board, (root->pos->row) + 2, (root->pos->col) + 2) == true) {
					return true;
				}
			}
		}
	}
	return false;
}
/*
	auxilary function for build tree for player funtion, recursive
	params:
	b - game's board
	src - player current position
	p - current player's type
	newRow - future player's row at the end of middle phase in turn
	newCol - future player's col at the end of middle phase in turn
	opponentRow - if during middle phase in turn a capture was made then delete opponent from the row and col
	opponentCol - if during middle phase in turn a capture was made then delete opponent from the row and col
	capturesSoFar - how many captures the player did during his current turn
	movesToGo - how many middle phases the player has during turn
	capturedDuringMove - 1 if a capture was made during last middle phase in turn
	return SingleSourceMovesTreeNode instnace in heap
*/
SingleSourceMovesTreeNode* BuildTreeForPlayerHelper(Board b, checkersPos* src, Player p, int newRow, int newCol, int opponentRow, int opponentCol,
	int capturesSoFar, int movesToGo, int capturedDuringMove) {
	//init instance of SingleSourceMovesTreeNode with previous board and new player pos and opponent skipped pos and captures so far
	SingleSourceMovesTreeNode* root = initSingleSingleSourceMovesTreeNode(b, newRow, newCol, opponentRow, opponentCol, capturesSoFar);
	//update player new pos on new board
	ChangePlayerPos(root->board, p, src, root->pos);
	//check first if you can skip from your location 
	if (canYouSkipLeft(root, root->pos, movesToGo, capturedDuringMove, p)) {
		if (p == PLAYER_B) {
			(root->next_move)[0] = BuildTreeForPlayerHelper(root->board, root->pos, p, (root->pos->row) - 2, (root->pos->col) - 2,
				(root->pos->row) - 1, (root->pos->col) - 1, capturesSoFar + 1, movesToGo - 1, 1);
		}
		else if (p == PLAYER_T) {
			(root->next_move)[0] = BuildTreeForPlayerHelper(root->board, root->pos, p, (root->pos->row) + 2, (root->pos->col) - 2,
				(root->pos->row) + 1, (root->pos->col) - 1, capturesSoFar + 1, movesToGo - 1, 1);
		}
	}
	if (canYouSkipRight(root, root->pos, movesToGo, capturedDuringMove, p)) {
		if (p == PLAYER_B) {
			(root->next_move)[1] = BuildTreeForPlayerHelper(root->board, root->pos, p, (root->pos->row) - 2, (root->pos->col) + 2,
				(root->pos->row) - 1, (root->pos->col) + 1, capturesSoFar + 1, movesToGo - 1, 1);
		}
		else if (p == PLAYER_T) {
			(root->next_move)[1] = BuildTreeForPlayerHelper(root->board, root->pos, p, (root->pos->row) + 2, (root->pos->col) + 2,
				(root->pos->row) + 1, (root->pos->col) + 1, capturesSoFar + 1, movesToGo - 1, 1);
		}
	}
	if (p == PLAYER_B) {
		//check if you havent made a skip, and you dont have future skips nearby, if not- check one squre nearby is free and you have turn
		if (movesToGo > 0 && CheckIfInBorder((root->pos->row) - 1, (root->pos->col) - 1) == true) {
			if (CheckIfSquareIsFree(root->board, (root->pos->row) - 1, (root->pos->col) - 1) == true) {
				(root->next_move)[0] = BuildTreeForPlayerHelper(root->board, root->pos, p, (root->pos->row) - 1, (root->pos->col) - 1,
					DONT_HAVE_AN_OPPENENT_TO_DELETE, DONT_HAVE_AN_OPPENENT_TO_DELETE, capturesSoFar, movesToGo - 1, 0);
			}
		}
		//check if you havent made a skip, and you dont have future skips nearby, if not- check one squre nearby is free and you have turn
		if (movesToGo > 0 && CheckIfInBorder((root->pos->row) - 1, (root->pos->col) + 1) == true) {
			if (CheckIfSquareIsFree(root->board, (root->pos->row) - 1, (root->pos->col) + 1) == true) {
				(root->next_move)[1] = BuildTreeForPlayerHelper(root->board, root->pos, p, (root->pos->row) - 1, (root->pos->col) + 1,
					DONT_HAVE_AN_OPPENENT_TO_DELETE, DONT_HAVE_AN_OPPENENT_TO_DELETE, capturesSoFar, movesToGo - 1, 0);
			}
		}
	}
	else if (p == PLAYER_T) {
		//check if you havent made a skip, and you dont have future skips nearby, if not- check one squre nearby is free and you have turn
		if (movesToGo > 0 && CheckIfInBorder((root->pos->row) + 1, (root->pos->col) - 1) == true) {
			if (CheckIfSquareIsFree(root->board, (root->pos->row) + 1, (root->pos->col) - 1) == true) {
				(root->next_move)[0] = BuildTreeForPlayerHelper(root->board, root->pos, p, (root->pos->row) + 1, (root->pos->col) - 1,
					DONT_HAVE_AN_OPPENENT_TO_DELETE, DONT_HAVE_AN_OPPENENT_TO_DELETE, capturesSoFar, movesToGo - 1, 0);
			}
		}
		//check if you havent made a skip, and you dont have future skips nearby, if not- check one squre nearby is free and you have turn
		if (movesToGo > 0 && CheckIfInBorder((root->pos->row) + 1, (root->pos->col) + 1) == true) {
			if (CheckIfSquareIsFree(root->board, (root->pos->row) + 1, (root->pos->col) + 1) == true) {
				(root->next_move)[1] = BuildTreeForPlayerHelper(root->board, root->pos, p, (root->pos->row) + 1, (root->pos->col) + 1,
					DONT_HAVE_AN_OPPENENT_TO_DELETE, DONT_HAVE_AN_OPPENENT_TO_DELETE, capturesSoFar, movesToGo - 1, 0);
			}
		}
	}
	return root;
}
/*
	create a SingleSingleSourceMovesTreeNode instance
	params:
	b- game's board
	newRow - future player's row at the end of middle phase in turn
	newCol - future player's col at the end of middle phase in turn
	opponentRow - if during middle phase in turn a capture was made then delete opponent from the row and col
	opponentCol - if during middle phase in turn a capture was made then delete opponent from the row and col
	capturesSoFar - how many captures the player did during his current turn
	return SingleSourceMovesTreeNode pointer to instance in heap
*/
SingleSourceMovesTreeNode* initSingleSingleSourceMovesTreeNode(Board b, int newRow, int newCol, int opponentRow, int opponentCol, int capturesSoFar) {
	int  i = 0;
	SingleSourceMovesTreeNode* root = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkIfAllocTreeNodeSucceded(root);
	DuplicateBoard(root->board, b);
	root->pos = (checkersPos*)malloc(sizeof(checkersPos));
	checkIfAllocCheckersPosSucceded(root->pos);
	root->pos->row = newRow;
	root->pos->col = newCol;
	if (opponentCol != DONT_HAVE_AN_OPPENENT_TO_DELETE) {
		DeleteOpponentFromPos(root->board, opponentRow, opponentCol);
	}
	root->total_captures_so_far = capturesSoFar;
	for (i = 0; i < 2; i++) {
		(root->next_move)[i] = NULL;
	}
	return root;
}

SingleSourceMovesTree* CreateNewSingleSourceMovesTree(Board board) {
	SingleSourceMovesTree* singleSourceMovesTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	checkIfAllocTreeSucceded(singleSourceMovesTree);
	return singleSourceMovesTree;
}

//branch 2

void freeTree(SingleSourceMovesTree* tr)
{
	if (tr == NULL)
		return;
	freeTreeRec(tr->source);
	free(tr);
}

void freeTreeRec(SingleSourceMovesTreeNode* source)
{
	if (source == NULL) {
		return;
	}
	free(source->pos);
	freeTreeRec(source->next_move[0]);
	freeTreeRec(source->next_move[1]);
	free(source);
}

