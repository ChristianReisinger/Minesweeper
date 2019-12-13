#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <board.h>
#include <geometry/geometry.h>
#include <geometry/console_ui.h>
#include <geometry/command_line.h>

#include <console_ui/console_ui.h>

static void query_restart(board* b, const board_geometry* g, const game_setup* setup) {
	printf("Start a new game? y/n\n");
	while (true) {
		char y_n;
		if (scanf(" %c", &y_n) != 1)
			continue;
		if (y_n == 'y' || y_n == 'Y') {
			init_board(b, setup);
			handle_user_input(b, g, setup);
		} else if (y_n == 'n' || y_n == 'N' || y_n == 'q' || y_n == 'Q')
			break;
	}
}

static void print_header(const board* b, const unsigned width, const time_t game_start_time) {
	char sep[width + 1];
	for (unsigned i = 0; i < width; ++i)
		sep[i] = '-';
	sep[width] = '\0';

	printf("%s\n", sep);

	unsigned pad_space_num = (width - 20) / 2;
	printf("|%*sArmed: %4d / %4d%*s|\n", pad_space_num, "", count_armed(b), b->num_mines, pad_space_num, "");

	int timer_seconds = (int) fmin(difftime(time(NULL), game_start_time), 359999.0);
	int hours = timer_seconds / 3600;
	int mins = (timer_seconds % 3600) / 60;
	int secs = (timer_seconds % 3600) % 60;

	printf("|%*sTime:     %02d:%02d:%02d%*s|\n", pad_space_num, "", hours, mins, secs, pad_space_num, "");

	printf("%s\n\n", sep);
}

static void refresh_ui(const board* b, const board_geometry* g, time_t game_start_time) {
	system("clear");
	print_header(b, get_ui_width(g), game_start_time);
	print_board(b, g);
}

static void print_won() {
	printf("You win!\n\n");
}

static void print_lost() {
	printf("You lose!\n\n");
}

static bool handle_action(bool* lost, board* b, const board_geometry* g, char action) {
	unsigned board_index;
	if ((action == 'a' || action == 'd' || action == 'r')
			&& read_board_index(&board_index, g)) {
		if (board_index < b->num_tiles)
			switch (action) {
				case 'a':
					arm(b, board_index);
					break;
				case 'd':
					disarm(b, board_index);
					break;
				case 'r':
					*lost = reveil(b, g, board_index);
					break;
			}
		return true;
	}
	return false;
}

void handle_user_input(board* b, const board_geometry* g, const game_setup* setup) {
	bool won = false, lost = false, quit = false;

	time_t game_start_time = time(NULL);

	refresh_ui(b, g, game_start_time);

	while (true) {
		char action;

		if (scanf(" %c", &action) == 1) {
			bool help_required = false;

			if (!handle_action(&lost, b, g, action)) {
				if (action == 'q')
					quit = true;
				else
					help_required = true;
			}

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
		query_restart(b, g, setup);
	}
}
