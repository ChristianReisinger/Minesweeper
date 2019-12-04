#include <stdio.h>
#include <stdlib.h>

#include <command_line_rect.h>
#include <board.h>
#include <geometry/geometry.h>
#include <geometry/console_ui.h>

#include <console_ui/console_ui.h>

static void query_restart(board* b, const board_geometry* g) {
	printf("Start a new game? y/n\n");
	while (true) {
		char y_n;
		if (scanf(" %c", &y_n) != 1)
			continue;
		if (y_n == 'y' || y_n == 'Y') {
			init_board(b);
			handle_user_input(b, g);
		} else if (y_n == 'n' || y_n == 'N' || y_n == 'q' || y_n == 'Q')
			break;
	}
}

static void refresh_ui(const board* b, const board_geometry* g, time_t game_start_time) {
	system("clear");
	print_header(b, g, game_start_time);
	print_board(b, g);
}

static void print_won() {
	printf("You win!\n\n");
}

static void print_lost() {
	printf("You lose!\n\n");
}

void handle_user_input(board* b, const board_geometry* g) {
	bool won = false, lost = false, quit = false;

	time_t game_start_time = time(NULL);

	refresh_ui(b, g, game_start_time);

	while (true) {
		char action;

		if (scanf(" %c", &action) == 1) {
			bool help_required = false;

			if (!handle_action(&lost, b, g, action) && action == 'q')
				quit = true;
			else
				help_required = true;

			won = is_won(b);

			refresh_ui(b, g, game_start_time);

			if (help_required)
				print_game_help();
			else if (quit)
				break;

			if (won || lost)
				break;
		}
	}

	if (!quit) {
		if (lost)
			print_lost();
		else if (won)
			print_won();
		query_restart(b, g);
	}
}
