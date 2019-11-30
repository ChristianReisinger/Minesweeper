#include <stdio.h>

#include <defs.h>
#include <command_line.h>
#include <util.h>
#include <board.h>
#include <geometry_rect.h>

int main(int argc, char** argv) {

	handle_GNU_options(argc, argv);

	board_geometry g = make_geometry(DEFAULT_ROW_NUM, DEFAULT_COL_NUM);
	board* minesweeper_board;
	allocate_board(&minesweeper_board, &g, get_tile_num(&g) * DEFAULT_MINE_FRACTION);

	free_board(&minesweeper_board);

	return 0;
}
