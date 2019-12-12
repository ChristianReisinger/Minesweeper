#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <console_ui/formatting.h>
#include <geometry/command_line.h>
#include <geometry/rectangle/types.h>

#include <geometry/console_ui.h>

static void print_row_sep(const board_geometry* g) {
	printf("    =");
	for (unsigned col = 0; col < g->num_cols; ++col)
		printf("====");
	printf("\n");
}

static void print_col_header(const board_geometry* g) {
	printf("    ");
	for (unsigned col = 0; col < g->num_cols; ++col) {
		printf(" ");
		print_centered_3digit(col);
	}
	printf("\n");
}

void print_header(const board* b, const board_geometry* g, const time_t game_start_time) {
	unsigned width = 10 + 4 * g->num_cols;
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

void print_board(const board* b, const board_geometry* g) {
	print_col_header(g);
	print_row_sep(g);
	for (unsigned row = 0; row < g->num_rows; ++row) {
		print_centered_3digit(row);
		printf(" |");
		for (unsigned col = 0; col < g->num_cols; ++col) {
			char state_str[64];
			get_state_string(b->state[get_index(row, col, g)], state_str, sizeof(state_str));
			printf("%s|", state_str);
		}
		printf(" ");
		print_centered_3digit(row);
		printf("\n");
		print_row_sep(g);
	}
	print_col_header(g);
}

bool handle_action(bool* lost, board* b, const board_geometry* g, char action) {
	int row, col;
	if ((action == 'a' || action == 'd' || action == 'r') && scanf("%d %d", &row, &col) == 2) {
		const unsigned board_index = get_index(row, col, g);
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
