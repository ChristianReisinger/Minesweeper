#include <stdlib.h>

#include <geometry/rectangle/types.h>

static unsigned DEFAULT_ROW_NUM = 10;
static unsigned DEFAULT_COL_NUM = 10;

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
	if(g == NULL)
		return MEMORY_ERR;

	g->num_rows = DEFAULT_ROW_NUM;
	g->num_cols = DEFAULT_COL_NUM;

	return SUCCESS;
}

error init_geometry(board_geometry* g, const game_setup* setup) {
	if(g == NULL || setup == NULL)
		return MEMORY_ERR;

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

	*adjacent_mine_num = 0;
	*adjacent_tile_num = 0;
	for (int row_shift = -1; row_shift <= 1; ++row_shift)
		for (int col_shift = -1; col_shift <= 1; ++col_shift) {
			const int curr_row = row + row_shift;
			const int curr_col = col + col_shift;
			if ((row_shift != 0 || col_shift != 0) && is_inside_board(curr_row, curr_col, g)) {
				++*adjacent_tile_num;
				if (mine_board[get_index(curr_row, curr_col, g)])
					++*adjacent_mine_num;
			}
		}
}

void get_adjacent_tile_indices(unsigned* adjacent_tile_indices, const board_geometry* g, unsigned board_index) {
	int row, col;
	get_pos(&row, &col, g, board_index);

	unsigned adjacent_tiles_found = 0;
	for (int row_shift = -1; row_shift <= 1; ++row_shift)
		for (int col_shift = -1; col_shift <= 1; ++col_shift) {
			const unsigned curr_row = row + row_shift;
			const unsigned curr_col = col + col_shift;
			if ((row_shift != 0 || col_shift != 0) && is_inside_board(curr_row, curr_col, g))
				adjacent_tile_indices[adjacent_tiles_found++] = get_index(curr_row, curr_col, g);
		}
}
