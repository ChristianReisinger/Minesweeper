#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include <defs.h>
#include <command_line.h>
#include <util.h>
#include <board.h>
#include <used_geometry.h>

#include <console_ui_rect.h>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");

	handle_GNU_options(argc, argv);

	board_geometry g = make_geometry(DEFAULT_ROW_NUM, DEFAULT_COL_NUM);
	board* minesweeper_board;
	allocate_board(&minesweeper_board, &g, get_tile_num(&g) * DEFAULT_MINE_FRACTION);
	init_board(minesweeper_board);

	print_board(minesweeper_board, &g);
	handle_user_input(minesweeper_board, &g);

	free_board(&minesweeper_board);

	return 0;
}
