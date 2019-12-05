#include <stdio.h>
#include <stdlib.h>
#include <defs.h>

#include <board.h>

error allocate_board(board** b, const board_geometry* g) {
	if ((*b = (board*) malloc(sizeof(board))) == NULL)
		return MEMORY_ERR;

	const unsigned num_tiles = get_tile_num(g);
	(*b)->num_tiles = num_tiles;

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

static error place_mines(board* b, int except_board_index) {
	if (b == NULL)
		return MEMORY_ERR;

	//to avoid discarding many random numbers, have at each tile a probability '#remaining_mines / #remaining_tiles' to place a mine;
	//which, at each tile, corresponds to a uniform probability '#total_mines / #total_tiles' to have a mine
	unsigned remaining_mines = b->num_mines;
	unsigned remaining_tiles = b->num_tiles;
	if (except_board_index >= 0 && except_board_index < (int) b->num_tiles)
		--remaining_tiles;

	debug_print("Distributing mines on board ...\n");
	for (unsigned i = 0; i < b->num_tiles && remaining_mines > 0; ++i, --remaining_tiles) {
		if (random_unsigned_from_zero_to_max(remaining_tiles - 1) < remaining_mines
				&& (int) i != except_board_index) {
			b->mined[i] = true;
			--remaining_mines;
		}
	}

	b->mines_placed = true;

	return SUCCESS;
}

error init_board(board* b, const game_setup* setup) {
	if (b == NULL)
		return MEMORY_ERR;

	const unsigned num_mines = get_mine_num(setup);

	if (num_mines >= b->num_tiles)
		return OVERFLOW_ERR;

	b->num_mines = num_mines;
	b->mines_placed = false;

	for (unsigned i = 0; i < b->num_tiles; ++i) {
		b->mined[i] = false;
		b->state[i] = STATE_HIDDEN;
	}

	return SUCCESS;
}

unsigned count_armed(const board* b) {
	unsigned num_armed = 0;
	for (unsigned i = 0; i < b->num_tiles; ++i)
		if (b->state[i] == STATE_ARMED)
			++num_armed;
	return num_armed;
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

bool is_won(board* b) {
	for (unsigned i = 0; i < b->num_tiles; ++i) {
		if (!(b->mined[i] || b->state[i] >= 0))
			return false;
	}

	for (unsigned i = 0; i < b->num_tiles; ++i)
		if (b->mined[i])
			b->state[i] = STATE_MINE_WON;

	return true;
}

static void reveil_mines(board* b, unsigned marked_index) {
	for (unsigned i = 0; i < b->num_tiles; ++i) {
		if (b->mined[i])
			b->state[i] = STATE_MINE;
	}
	b->state[marked_index] = STATE_MINE_MARKED;
}

static bool reveil_adjacent_if_safe(board* b, const board_geometry* g, unsigned board_index) {
	unsigned adjacent_mine_num, adjacent_tile_num;
	get_adjacent_nums(&adjacent_tile_num, &adjacent_mine_num, b->mined, g, board_index);

	unsigned adjacent_tile_indices[adjacent_tile_num];
	get_adjacent_tile_indices(adjacent_tile_indices, g, board_index);

	int* state = (b->state) + board_index;
	if (*state == STATE_HIDDEN)
		*state = adjacent_mine_num;
	else if (*state > 0) {
		unsigned num_armed = 0;
		for (unsigned i = 0; i < adjacent_tile_num; ++i)
			if (b->state[adjacent_tile_indices[i]] == STATE_ARMED)
				++num_armed;
		adjacent_mine_num -= num_armed;
	}

	if (adjacent_mine_num == 0)
		for (unsigned i = 0; i < adjacent_tile_num; ++i)
			if (b->state[adjacent_tile_indices[i]] == STATE_HIDDEN
					&& reveil(b, g, adjacent_tile_indices[i]))
				return true;

	return false;
}

bool reveil(board* b, const board_geometry* g, unsigned board_index) {
	if (!b->mines_placed) {
		place_mines(b, board_index);
		return reveil(b, g, board_index);
	} else if (b->state[board_index] == STATE_ARMED) {
		printf("This tile is armed!\n");
		return false;
	} else if (b->mined[board_index]) {
		reveil_mines(b, board_index);
		return true;
	} else
		return reveil_adjacent_if_safe(b, g, board_index);
}
