#include <stdio.h>
#include <stdlib.h>

#include <board.h>

error allocate_board(board** b, const board_geometry* g, unsigned num_mines) {
	const unsigned num_tiles = get_tile_num(g);

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

void arm(board* b, unsigned board_index) {
	int* state = (b->state) + board_index;
	if (*state == STATE_HIDDEN)
		*state = STATE_ARMED;
}

void disarm(board* b, unsigned board_index) {
	int* state = (b->state) + board_index;
	if (*state == STATE_ARMED)
		*state = STATE_HIDDEN;
}

static void reveil_mines(board* b, unsigned marked_index) {
	for (unsigned i = 0; i < b->num_tiles; ++i) {
		if (b->mined[i])
			b->state[i] = STATE_MINE;
	}
	b->state[marked_index] = STATE_MINE_MARKED;
}

bool reveil(board* b, const board_geometry* g, unsigned board_index) {
	int* state = (b->state) + board_index;

	if (*state == STATE_ARMED) {
		printf("This tile is armed!\n");
		return false;
	} else if (b->mined[board_index]) {
		reveil_mines(b, board_index);
		return true;
	} else {
		unsigned adjacent_mine_num, adjacent_tile_num;
		get_adjacent_nums(&adjacent_tile_num, &adjacent_mine_num, b->mined, g, board_index);

		unsigned adjacent_tile_indices[adjacent_tile_num];
		get_adjacent_tile_indices(adjacent_tile_indices, g, board_index);

		if (*state == STATE_HIDDEN)
			*state = adjacent_mine_num;
		else if (*state > 0) {
			unsigned num_armed = 0;
			for (int i = 0; i < adjacent_tile_num; ++i)
				if (b->state[adjacent_tile_indices[i]] == STATE_ARMED)
					++num_armed;
			adjacent_mine_num -= num_armed;
		}

		if (adjacent_mine_num == 0)
			for (int i = 0; i < adjacent_tile_num; ++i)
				if (b->state[adjacent_tile_indices[i]] == STATE_HIDDEN
						&& reveil(b, g, adjacent_tile_indices[i]))
					return true;
	}
	return false;
}
