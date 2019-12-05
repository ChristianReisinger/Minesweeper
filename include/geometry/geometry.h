#include <stdbool.h>

#include <util.h>
#include <geometry/command_line.h>

#ifndef INCLUDE_GEOMETRY_GEOMETRY_H_
#define INCLUDE_GEOMETRY_GEOMETRY_H_

typedef struct board_geometry board_geometry;

unsigned get_index(int row, int col, const board_geometry* g);

error alloc_geometry(board_geometry** g);
error init_default_geometry(board_geometry* g);
error init_geometry(board_geometry* g, const game_setup* setup);
void free_geometry(board_geometry** g);

unsigned get_tile_num(const board_geometry* g);

void get_adjacent_nums(unsigned* adjacent_tile_num, unsigned* adjacent_mine_num,
		const bool* mine_board, const board_geometry* g, unsigned board_index);

void get_adjacent_tile_indices(unsigned* adjacent_tile_indices, const board_geometry* g, unsigned board_index);

#endif
