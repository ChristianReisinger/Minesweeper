#include <stdbool.h>

#ifndef INCLUDE_BOARD_H_
#define INCLUDE_BOARD_H_

typedef enum {
	SUCCESS,
	MEMORY_ERR,
	OVERFLOW_ERR
} board_error;

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

board_error allocate_board(board** b, unsigned num_tiles, unsigned num_mines);
void free_board(board** b);

board_error init_board(board* b);

#endif
