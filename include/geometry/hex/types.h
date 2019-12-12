#include <geometry/geometry.h>
#include <geometry/command_line.h>

#ifndef INCLUDE_GEOMETRY_HEX_TYPES_H_
#define INCLUDE_GEOMETRY_HEX_TYPES_H_

struct board_geometry {
	unsigned num_rows, num_cols;
};

struct game_setup {
	unsigned num_rows;
	unsigned num_cols;
	unsigned num_mines;
};

#endif
