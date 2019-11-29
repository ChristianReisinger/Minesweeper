#include <stdlib.h>

#include <util.h>

#include <board.h>

board_error allocate_board(board** b, unsigned num_rows, unsigned num_cols, unsigned num_mines) {
	if (num_mines > num_rows * num_cols)
		return OVERFLOW_ERR;

	if ((*b = (board*) malloc(sizeof(board))) == NULL)
		return MEMORY_ERR;

	(*b)->num_rows = num_rows;
	(*b)->num_cols = num_cols;
	(*b)->num_mines = num_mines;

	if (((*b)->mined = (bool*) malloc(num_rows * num_cols * sizeof(bool))) == NULL) {
		free(*b);
		return MEMORY_ERR;
	}

	if (((*b)->state = (board_state*) malloc(num_rows * num_cols * sizeof(board_state))) == NULL) {
		free(*b);
		free((*b)->mined);
		return MEMORY_ERR;
	}

	return SUCCESS;
}

void free_board(board** b) {
	if (*b != NULL) {
		free((*b)->mined);
		free((*b)->state);
		free((*b));
		*b = NULL;
	}
}

static board_error place_mines(board* b) {
	if (b == NULL)
		return MEMORY_ERR;

	const unsigned total_tiles = b->num_rows * b->num_cols;

	for (int i = 0; i < total_tiles; ++i)
		b->mined[i] = false;

	//to avoid discarding many random numbers, have at each tile a probability '#remaining_mines / #remaining_tiles' to place a mine;
	//which, at each tile, corresponds to a uniform probability '#total_mines / #total_tiles' to have a mine
	unsigned remaining_mines = b->num_mines;
	for (unsigned i = 0; i < total_tiles && remaining_mines > 0; ++i) {
		const unsigned remaining_tiles = total_tiles - i;
		if (random_unsigned_from_zero_to_max(remaining_tiles - 1) < remaining_mines) {
			b->mined[i] = true;
			--remaining_mines;
		}
	}

	return SUCCESS;
}

board_error init_board(board* b) {
	if (b == NULL)
		return MEMORY_ERR;

	for (int i = 0; i < b->num_rows * b->num_cols; ++i)
		b->state[i] = HIDDEN;

	return place_mines(b);
}
