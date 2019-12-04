#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include <defs.h>
#include <util.h>
#include <board.h>
#include <command_line_rect.h>
#include <console_ui/console_ui.h>
#include <geometry/geometry.h>


int main(int argc, char** argv) {
	setlocale(LC_ALL, "");

	game_setup setup = handle_GNU_options(argc, argv);

	board_geometry* g;
	alloc_geometry(&g, &setup);

	board* minesweeper_board;
	allocate_board(&minesweeper_board, g, setup.num_mines);

	init_board(minesweeper_board);
	handle_user_input(minesweeper_board, g);

	free_board(&minesweeper_board);
	free_geometry(&g);

	return 0;
}
