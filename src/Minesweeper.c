#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>

#include <defs.h>
#include <util.h>
#include <board.h>
#include <console_ui/console_ui.h>
#include <geometry/command_line.h>
#include <geometry/geometry.h>

void fatal_error() {
	printf("Fatal error, exiting ...\n");
	exit(1);
}

void regular_error(char* err_message) {
	printf("Error: %s\n", err_message);
	exit(0);
}

int main(int argc, char** argv) {
	game_setup* setup;
	if (alloc_game_setup(&setup) != SUCCESS)
		fatal_error();
	handle_GNU_options(argc, argv, setup);

	board_geometry* g;
	if (alloc_geometry(&g) != SUCCESS)
		fatal_error();
	error err = init_geometry(g, setup);
	if (err == SIZE_ERR)
		regular_error("the board is too small!");
	else if (err != SUCCESS)
		fatal_error();

	board* minesweeper_board;
	if (allocate_board(&minesweeper_board, g) != SUCCESS)
		fatal_error();
	err = init_board(minesweeper_board, setup);
	if (err == SIZE_ERR)
		regular_error("too many mines!");
	else if (err != SUCCESS)
		fatal_error();

	handle_user_input(minesweeper_board, g, setup);

	free_game_setup(&setup);
	free_board(&minesweeper_board);
	free_geometry(&g);

	return 0;
}
