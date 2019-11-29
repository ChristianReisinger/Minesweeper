#include <stdbool.h>

#ifndef INCLUDE_GEOMETRY_RECT_H_
#define INCLUDE_GEOMETRY_RECT_H_

#define DEFAULT_ROW_NUM 10
#define DEFAULT_COL_NUM 10

typedef struct s_board_geometry {
	unsigned num_rows, num_cols;
} board_geometry;

board_geometry make_geometry(unsigned num_rows, unsigned num_cols);

void get_pos(int* row, int* col, const board_geometry* g, unsigned board_index);
unsigned get_index(int row, int col, const board_geometry* g);

unsigned get_tile_num(const board_geometry* g);

bool is_inside_board(int row, int col, const board_geometry* g);

void get_adjacent_nums(unsigned* adjacent_tile_num, unsigned* adjacent_mine_num,
		const bool* mine_board, const board_geometry* g, unsigned board_index);

void get_adjacent_tile_indices(unsigned* adjacent_tile_indices, const board_geometry* g, unsigned board_index);

#endif
