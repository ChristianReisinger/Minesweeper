#include <stdbool.h>

#include <util.h>
#include <board.h>

#ifndef INCLUDE_GEOMETRY_RECT_H_
#define INCLUDE_GEOMETRY_RECT_H_

typedef struct s_board_geometry {
	unsigned num_rows, num_cols;
} board_geometry;

board_geometry make_geometry(const board* b, unsigned num_rows, error* err);

void get_pos(int* row, int* col, const board_geometry* g, unsigned board_index);
unsigned get_index(int row, int col, const board_geometry* g);

bool is_inside_board(int row, int col, const board_geometry* g);

unsigned get_adjacent_mine_num(const board* b, const board_geometry* g, unsigned board_index);

#endif
