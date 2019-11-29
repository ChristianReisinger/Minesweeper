#include <stdlib.h>

#include <board.h>

error allocate_board(board** b, unsigned num_tiles, unsigned num_mines) {
	if (num_mines > num_tiles)
		return OVERFLOW_ERR;

	if ((*b = (board*) malloc(sizeof(board))) == NULL)
		return MEMORY_ERR;

	(*b)->num_tiles = num_tiles;
	(*b)->num_mines = num_mines;

	if (((*b)->mined = (bool*) malloc(num_tiles * sizeof(bool))) == NULL) {
		free(*b);
		return MEMORY_ERR;
	}

	if (((*b)->state = (int*) malloc(num_tiles * sizeof(int))) == NULL) {
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

static error place_mines(board* b) {
	if (b == NULL)
		return MEMORY_ERR;

	for (int i = 0; i < b->num_tiles; ++i)
		b->mined[i] = false;

	//to avoid discarding many random numbers, have at each tile a probability '#remaining_mines / #remaining_tiles' to place a mine;
	//which, at each tile, corresponds to a uniform probability '#total_mines / #total_tiles' to have a mine
	unsigned remaining_mines = b->num_mines;
	for (unsigned i = 0; i < b->num_tiles && remaining_mines > 0; ++i) {
		const unsigned remaining_tiles = b->num_tiles - i;
		if (random_unsigned_from_zero_to_max(remaining_tiles - 1) < remaining_mines) {
			b->mined[i] = true;
			--remaining_mines;
		}
	}

	return SUCCESS;
}

error init_board(board* b) {
	if (b == NULL)
		return MEMORY_ERR;

	for (int i = 0; i < b->num_tiles; ++i)
		b->state[i] = STATE_HIDDEN;

	return place_mines(b);
}
