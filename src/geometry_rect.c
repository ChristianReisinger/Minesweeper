#include <stddef.h>

#include <geometry_rect.h>

board_geometry make_geometry(const board* b, unsigned num_rows, error* err) {
	if (b->num_tiles % num_rows != 0)
		*err = OVERFLOW_ERR;
	else
		*err = SUCCESS;

	const unsigned num_cols = b->num_tiles / num_rows;
	board_geometry g = {
			.num_rows = num_rows,
			.num_cols = num_cols
	};
	return g;
}

void get_pos(int* row, int* col, const board_geometry* g, unsigned board_index) {
	*row = board_index / g->num_cols;
	*col = board_index % g->num_cols;
}

unsigned get_index(int row, int col, const board_geometry* g) {
	return col + g->num_cols * row;
}

bool is_inside_board(int row, int col, const board_geometry* g) {
	return row >= 0 && row < g->num_rows && col >= 0 && col < g->num_cols;
}

void get_adjacent_nums(unsigned* adjacent_tile_num, unsigned* adjacent_mine_num,
		const board* b, const board_geometry* g, unsigned board_index) {
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
				if (b->mined[get_index(curr_row, curr_col, g)])
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
