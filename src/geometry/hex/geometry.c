#include <stdlib.h>

#include <geometry/hex/types.h>

/*
 \col 0   1   2   3   4
 row ___     ___     ___
 0  / 0 \___/ 2 \___/ 4 \  0
 .  \___/ 1 \___/ 3 \___/
 1  / 5 \___/ 7 \___/ 9 \  1
 .  \___/ 6 \___/ 8 \___/
 2  / 10\___/ 12\___/ 14\  2
 .  \___/ 11\___/ 13\___/
 .      \___/   \___/
 .    0   1   2   3   4
 */

#define ADJACENT_TILE_NUM 6

static const unsigned DEFAULT_ROW_NUM = 9;
static const unsigned DEFAULT_COL_NUM = 10;
static const unsigned MIN_ROW_NUM = 4;
static const unsigned MIN_COL_NUM = 4;

struct pos_shift {
	int row_shift, col_shift;
};

static void get_adjacent_tile_shifts(struct pos_shift* shifts, int col) {
	const int col_dependent_row_shift = (col % 2 == 0) ? -1 : 1;

	struct pos_shift temp[ADJACENT_TILE_NUM] = {
			{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 },
			{ col_dependent_row_shift, -1 }, { col_dependent_row_shift, 1 }
	};
	for (int i = 0; i < ADJACENT_TILE_NUM; ++i)
		shifts[i] = temp[i];
}

static void get_pos(int* row, int* col, const board_geometry* g, unsigned board_index) {
	*row = board_index / g->num_cols;
	*col = board_index % g->num_cols;
}

static bool is_inside_board(int row, int col, const board_geometry* g) {
	return row >= 0 && row < (int) g->num_rows && col >= 0 && col < (int) g->num_cols;
}

unsigned get_index(int row, int col, const board_geometry* g) {
	return col + g->num_cols * row;
}

error alloc_geometry(board_geometry** g) {
	if ((*g = (board_geometry*) malloc(sizeof(board_geometry))) == NULL)
		return MEMORY_ERR;

	return SUCCESS;
}

error init_default_geometry(board_geometry* g) {
	if (g == NULL)
		return MEMORY_ERR;

	g->num_rows = DEFAULT_ROW_NUM;
	g->num_cols = DEFAULT_COL_NUM;

	return SUCCESS;
}
error init_geometry(board_geometry* g, const game_setup* setup) {
	if (g == NULL || setup == NULL)
		return MEMORY_ERR;

	if (setup->num_rows < MIN_ROW_NUM || setup->num_cols < MIN_COL_NUM)
		return SIZE_ERR;

	g->num_rows = setup->num_rows;
	g->num_cols = setup->num_cols;

	return SUCCESS;
}

void free_geometry(board_geometry** g) {
	if (*g != NULL) {
		free(*g);
		*g = NULL;
	}
}

unsigned get_tile_num(const board_geometry* g) {
	return g->num_rows * g->num_cols;
}

void get_adjacent_nums(unsigned* adjacent_tile_num, unsigned* adjacent_mine_num,
		const bool* mine_board, const board_geometry* g, unsigned board_index) {
	int row, col;
	get_pos(&row, &col, g, board_index);
	struct pos_shift adjacent_tile_shifts[ADJACENT_TILE_NUM];
	get_adjacent_tile_shifts(adjacent_tile_shifts, col);

	*adjacent_mine_num = 0;
	*adjacent_tile_num = 0;

	for (int i = 0; i < ADJACENT_TILE_NUM; ++i) {
		const int curr_row = row + adjacent_tile_shifts[i].row_shift;
		const int curr_col = col + adjacent_tile_shifts[i].col_shift;
		if (is_inside_board(curr_row, curr_col, g)) {
			++*adjacent_tile_num;
			if (mine_board[get_index(curr_row, curr_col, g)])
				++*adjacent_mine_num;
		}
	}
}

void get_adjacent_tile_indices(unsigned* adjacent_tile_indices, const board_geometry* g, unsigned board_index) {
	int row, col;
	get_pos(&row, &col, g, board_index);
	struct pos_shift adjacent_tile_shifts[ADJACENT_TILE_NUM];
	get_adjacent_tile_shifts(adjacent_tile_shifts, col);

	unsigned adjacent_tiles_found = 0;
	for (int i = 0; i < ADJACENT_TILE_NUM; ++i) {
		const int curr_row = row + adjacent_tile_shifts[i].row_shift;
		const int curr_col = col + adjacent_tile_shifts[i].col_shift;
		if (is_inside_board(curr_row, curr_col, g))
			adjacent_tile_indices[adjacent_tiles_found++] = get_index(curr_row, curr_col, g);
	}
}
