#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h> 

#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 8
#define PLAYER_T 'T'
#define PLAYER_B 'B'
#define EMPTY_CELL ' '
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define DONT_HAVE_AN_OPPENENT_TO_DELETE -1
#define FIRST_ROW 0
#define LAST_ROW 7
#define NO_WINNER '\0'

typedef struct checkersPos {
	char row;
	char col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
typedef struct _SingleSourceMovesTreeNode {
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode* next_move[2];
}SingleSourceMovesTreeNode;
typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;

//branch 2
typedef struct _SingleSourceMovesListCell
{
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList
{
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;

}SingleSourceMovesList;

//branch 3
typedef struct _multiplesSourceMovesListCell
{
	SingleSourceMovesList* single_source_moves_list;
	struct _multipleSourceMovesListCell* next;
}MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList
{
	MultipleSourceMovesListCell* head;
	MultipleSourceMovesListCell* tail;
}MultipleSourceMovesList;