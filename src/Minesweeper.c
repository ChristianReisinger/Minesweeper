#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include <defs.h>
#include <util.h>
#include <board.h>
#include <console_ui/console_ui.h>
#include <geometry/command_line.h>
#include <geometry/geometry.h>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");

	game_setup* setup;
	alloc_game_setup(&setup);
	handle_GNU_options(argc, argv, setup);

	board_geometry* g;
	alloc_geometry(&g);
	init_geometry(g, setup);

	board* minesweeper_board;
	allocate_board(&minesweeper_board, g);
	init_board(minesweeper_board, setup);

	handle_user_input(minesweeper_board, g, setup);

	free_game_setup(&setup);
	free_board(&minesweeper_board);
	free_geometry(&g);

	return 0;
}
