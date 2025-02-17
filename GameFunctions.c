
#include "GameFunctionsHeader.h"

/*
	check possible moves available in player's turn
	params:
	board - game's board
	player - the player which has the turn
*/
void Turn(Board board, Player player)
{
	MultipleSourceMovesList* best_moves_list;
	MultipleSourceMovesListCell* current;
	MultipleSourceMovesListCell* best_square_to_move_from;
	SingleSourceMovesListCell* iterator;
	unsigned int capture_counter = 0;
	checkersPos prevPos, newPos;
	//get list of current best moves
	best_moves_list = FindAllPossiblePlayerMoves(board, player);

	//initialize best_square as the first square in the list
	best_square_to_move_from = best_moves_list->head;
	current = best_square_to_move_from->next;

	while (current != NULL)
	{
		//
		if (current->single_source_moves_list->tail->captures > best_square_to_move_from->single_source_moves_list->tail->captures)
		{
			best_square_to_move_from = current;
		}
		else if (current->single_source_moves_list->tail->captures == best_square_to_move_from->single_source_moves_list->tail->captures)
		{
			best_square_to_move_from = getBestSquareToMoveFrom(player, best_square_to_move_from, current);
		}

		current = current->next;
	}

	//move player to last position
	prevPos.row = best_square_to_move_from->single_source_moves_list->head->position->row;
	prevPos.col = best_square_to_move_from->single_source_moves_list->head->position->col;

	newPos.row = best_square_to_move_from->single_source_moves_list->tail->position->row;
	newPos.col = best_square_to_move_from->single_source_moves_list->tail->position->col;

	//print player's move
	printTurn(&prevPos, &newPos);

	//change player's position after move
	ChangePlayerPos(board, player, &prevPos, &newPos);

	//delete opponents
	iterator = best_square_to_move_from->single_source_moves_list->head;

	while (iterator->next != NULL)
	{
		capture_counter += iterator->captures;
		if (iterator->next->captures == (iterator->captures) + 1)
		{
			DeleteOpponentFromBoard(board, player, iterator->position, iterator->next->position);
		}

		iterator = iterator->next;
	}

	freeMultipleSourceMovesList(best_moves_list);
}

void printTurn(checkersPos* prevPos, checkersPos* newPos)// print player's move
{
	char rows[BOARD_SIZE] = { 'A','B','C','D','E', 'F', 'G', 'H' };

	printf("%c%d->%c%d\n", rows[prevPos->row], prevPos->col + 1, rows[newPos->row], newPos->col + 1);
}
/*
	play the game
	params:
	board - game's actual board
	starting_player - starting player of game
*/
void PlayGame(Board board, Player starting_player)// play game until there is a winner
{
	Player winner, currPlayer = starting_player, player_with_biggest_num_of_captures;
	unsigned int numOfMovesB = 0, numOfMovesT = 0, captureSumB = 0, captureSumT = 0,
		currNumOfCaptures = 0, biggestNumOfCaptures = 0, numOfPawnsBeforeTurn = 0, numOfPawnsAfterTurn = 0;
	InitBoard(board);
	PrintBoard(board);

	while (!isWinnerFound(board, &winner))
	{
		printf("%c's turn:\n", currPlayer);

		//count number of opponents before turn
		numOfPawnsBeforeTurn = countNumOfPawns(board, currPlayer);

		//increase number of moves
		currPlayer == PLAYER_B ? ++numOfMovesB : ++numOfMovesT;
		//make a move
		Turn(board, currPlayer);
		PrintBoard(board);
		//count number of opponents after turn
		numOfPawnsAfterTurn = countNumOfPawns(board, currPlayer);
		currNumOfCaptures = numOfPawnsBeforeTurn - numOfPawnsAfterTurn;
		updateBiggestnumOfCaptures(&currNumOfCaptures, &biggestNumOfCaptures, currPlayer, &player_with_biggest_num_of_captures);
		SwitchPlayer(&currPlayer);
	}

	printf("%c wins!\n", winner);
	printf("%c performed %u moves\n", winner, winner == PLAYER_B ? numOfMovesB : numOfMovesT);
	printf("%c performed the highest number of captures in a single move - %u\n", player_with_biggest_num_of_captures, biggestNumOfCaptures);
}
/*
	after the turn has made we need to check if maximum num of captures in single move needs to be changed, base on turn's results
	currNumOfCaptures - how many captures the player which made the current turn did
	biggestNumOfCaptures - variable which stores the biggest num of captures. can be updated during func
	currPlayer - who is the player which did the current turn
	player_with_biggest_num_of_captures - variable which store the type of player which has the biggest num of captures. can be updated during func
*/
void updateBiggestnumOfCaptures(int* currNumOfCaptures, int* biggestNumOfCaptures, Player currPlayer, Player* player_with_biggest_num_of_captures) {
	if (*currNumOfCaptures >= *biggestNumOfCaptures && currPlayer == PLAYER_B)
	{
		*biggestNumOfCaptures = *currNumOfCaptures;
		*player_with_biggest_num_of_captures = PLAYER_B;
	}
	else if (*currNumOfCaptures >= *biggestNumOfCaptures && currPlayer == PLAYER_T)
	{
		*biggestNumOfCaptures = *currNumOfCaptures;
		*player_with_biggest_num_of_captures = PLAYER_T;
	}
}
/*
	check if we can announce a winner and finish the game
	params:
	board - game's board
	winner - output variable to store winner, if exists
	return true if we found a winner,false otherwise
*/
bool isWinnerFound(Board board, Player* winner) //return true if one of the players has won
{
	unsigned int i, j, countBPlayers = 0, countTPlayers = 0;

	if (checkIfPlayerIsAtLastLineOfOpponent(winner, board) == true) {
		return true;
	}

	//check if one of the players has no more pawns
	return  checkIfPlayerHasNoPawnsLeft(board, winner);
}
/*
	check if some of player is at the last line of its opponent
	params:
	winner - output variable to store winner, if exists
	board -  game's board
	return true if some of player is at the last line of its opponent
*/
bool checkIfPlayerIsAtLastLineOfOpponent(Player* winner, Board board) {
	int j = 0;
	for (j = 0; j < BOARD_SIZE; j++)
	{
		//if there is a B player in the first row or a T player in the last row
		if (board[FIRST_ROW][j] == PLAYER_B)
		{
			*winner = PLAYER_B;
			return true;
		}
		if (board[LAST_ROW][j] == PLAYER_T)
		{
			*winner = PLAYER_T;
			return true;
		}
	}
}
/*
*	check if some of the players doesnt have more active pawns
*	params:
*	winner - output variable to store winner, if exists
	board -  game's board
*/
bool checkIfPlayerHasNoPawnsLeft(Board board, Player* winner) {
	int i, j, countBPlayers = 0, countTPlayers = 0;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == PLAYER_B)
				countBPlayers++;
			else if (board[i][j] == PLAYER_T)
				countTPlayers++;
		}
	}
	if (countBPlayers == 0)
	{
		*winner = PLAYER_B;
		return true;
	}
	else if (countTPlayers == 0)
	{
		*winner = PLAYER_T;
		return true;
	}
	else
	{
		*winner = NO_WINNER;
		return false;
	}
}