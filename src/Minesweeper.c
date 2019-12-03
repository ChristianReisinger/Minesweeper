#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include <defs.h>
#include <command_line_rect.h>
#include <util.h>
#include <board.h>
#include <used_geometry.h>

#include <console_ui_rect.h>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");

	game_setup setup = handle_GNU_options(argc, argv);

	board_geometry g = make_geometry(&setup);
	board* minesweeper_board;
	allocate_board(&minesweeper_board, &g, setup.num_mines);
	init_board(minesweeper_board);

	handle_user_input(minesweeper_board, &g);

	free_board(&minesweeper_board);

	return 0;
}
