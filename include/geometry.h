#include <stdbool.h>

#include <command_line_rect.h>

#ifndef INCLUDE_GEOMETRY_H_
#define INCLUDE_GEOMETRY_H_

typedef struct board_geometry board_geometry;

unsigned get_index(int row, int col, const board_geometry* g);

board_geometry get_default_geometry();
board_geometry make_geometry(const game_setup* setup);

unsigned get_tile_num(const board_geometry* g);

void get_adjacent_nums(unsigned* adjacent_tile_num, unsigned* adjacent_mine_num,
		const bool* mine_board, const board_geometry* g, unsigned board_index);

void get_adjacent_tile_indices(unsigned* adjacent_tile_indices, const board_geometry* g, unsigned board_index);

#endif
