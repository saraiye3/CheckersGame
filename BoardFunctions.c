#include "Main.h"
#include "BoardFunctionsHeader.h"
/*
	auxilary function for DeleteOpponentFromBoard
	params:
	b- game's board
	row - row which opponent is located and needs to be removed
	col - col which opponent is located and needs to be removed
*/
void DeleteOpponentFromPos(Board b, int row, int col) {
	b[row][col] = ' ';
}
/*
	change player position according to future position in current move
*/
void ChangePlayerPos(Board b, Player p, checkersPos* oldPos, checkersPos* newPos) {
	b[oldPos->row][oldPos->col] = ' ';
	b[newPos->row][newPos->col] = p;
}
/*
	check if given spot is in border
*/
bool CheckIfInBorder(int row, int col) {
	if (row >= 0 && row < BOARD_SIZE) {
		if (col >= 0 && col < BOARD_SIZE) {
			return true;
		}
	}
	return false;
}
/*
	check if given spot in border is free
*/
bool CheckIfSquareIsFree(Board b, int row, int col) {
	if (b[row][col] == ' ') {
		return true;
	}
	else {
		return false;
	}
}
/*
	duplicate src board content to dest board
*/
void DuplicateBoard(Board dest, Board src) {
	int i = 0, j = 0;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			dest[i][j] = src[i][j];
		}
	}
}
/*
	set board to starting point
*/
void InitBoard(Board b) {
	int i = 0, j = 0;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if ((i + (j + 1)) % 2 == 0) {
				if (i == A || i == B || i == C) {
					b[i][j] = 'T';
				}
				else if (i == G || i == F || i == H) {
					b[i][j] = 'B';
				}
				else {
					b[i][j] = ' ';
				}
			}
			else {
				b[i][j] = ' ';
			}
		}
	}
}

/*
	switch turns - player T wiil become B and opposite
*/
void SwitchPlayer(Player* player) {
	if ((*player) == PLAYER_B)
		(*player) = PLAYER_T;
	else
		*player = PLAYER_B;
}

/*
	print current board
*/
void PrintBoard(Board b) {
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("+ |1|2|3|4|5|6|7|8|\n");
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("|A|%c|%c|%c|%c|%c|%c|%c|%c|\n", b[0][0], b[0][1], b[0][2], b[0][3], b[0][4], b[0][5], b[0][6], b[0][7]);
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("|B|%c|%c|%c|%c|%c|%c|%c|%c|\n", b[1][0], b[1][1], b[1][2], b[1][3], b[1][4], b[1][5], b[1][6], b[1][7]);
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("|C|%c|%c|%c|%c|%c|%c|%c|%c|\n", b[2][0], b[2][1], b[2][2], b[2][3], b[2][4], b[2][5], b[2][6], b[2][7]);
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("|D|%c|%c|%c|%c|%c|%c|%c|%c|\n", b[3][0], b[3][1], b[3][2], b[3][3], b[3][4], b[3][5], b[3][6], b[3][7]);
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("|E|%c|%c|%c|%c|%c|%c|%c|%c|\n", b[4][0], b[4][1], b[4][2], b[4][3], b[4][4], b[4][5], b[4][6], b[4][7]);
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("|F|%c|%c|%c|%c|%c|%c|%c|%c|\n", b[5][0], b[5][1], b[5][2], b[5][3], b[5][4], b[5][5], b[5][6], b[5][7]);
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("|G|%c|%c|%c|%c|%c|%c|%c|%c|\n", b[6][0], b[6][1], b[6][2], b[6][3], b[6][4], b[6][5], b[6][6], b[6][7]);
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("|H|%c|%c|%c|%c|%c|%c|%c|%c|\n", b[7][0], b[7][1], b[7][2], b[7][3], b[7][4], b[7][5], b[7][6], b[7][7]);
	printf("+-+-+-+-+-+-+-+-+-+\n");
}
/*
	delete opponent from board based on player skip options, if skip options exist
	params:
	board - board's game
	player - current player which plays the turn
	prevPos - current position of player in turn
	nextPos - future position of player after a skip is made

*/
void DeleteOpponentFromBoard(Board board, Player player, checkersPos* prevPos, checkersPos* nextPos)
{
	if (player == PLAYER_T)
	{
		if (nextPos->col > prevPos->col)
		{
			DeleteOpponentFromPos(board, prevPos->row + 1, prevPos->col + 1);
		}
		else
		{
			DeleteOpponentFromPos(board, prevPos->row + 1, prevPos->col - 1);
		}
	}
	else //if the player is B
	{
		if (nextPos->col > prevPos->col)
		{
			DeleteOpponentFromPos(board, prevPos->row - 1, prevPos->col + 1);
		}
		else
		{
			DeleteOpponentFromPos(board, prevPos->row - 1, prevPos->col - 1);
		}
	}
}
/*
	count number of pawns the opponent of player has
	params:
	board - game's board
	player - which player has the turn now
	return the num of pawn the opponent of player has in board
*/
unsigned int countNumOfPawns(Board board, Player player)
{
	unsigned int countAppearances = 0, i, j;
	SwitchPlayer(&player);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == player)
				countAppearances++;
		}
	}

	return countAppearances;
}