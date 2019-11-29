#include <stdbool.h>

#include <util.h>

#ifndef INCLUDE_BOARD_H_
#define INCLUDE_BOARD_H_

typedef enum {
	HIDDEN,
	REVEILED,
	ARMED
} board_state;

typedef struct {
	unsigned num_tiles, num_mines;
	bool* mined;
	board_state* state;
} board;

error allocate_board(board** b, unsigned num_tiles, unsigned num_mines);
void free_board(board** b);

error init_board(board* b);

#endif
