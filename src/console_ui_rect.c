#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <command_line.h>
#include <board.h>
#include <geometry_rect.h>

#include <console_ui_rect.h>

static void get_state_char(int state, char* buf, unsigned buf_size) {
	if (buf == NULL || buf_size < 64)
		return;

	switch(state) {
		case STATE_ARMED:
			strncpy(buf, "\033[48;2;80;80;80m\033[38;2;255;30;30m \u2691 \033[0m", buf_size);
			break;
		case STATE_HIDDEN:
			strncpy(buf, "\033[38;2;150;150;150m\u2588\u2588\u2588\033[0m", buf_size);
			break;
		case STATE_MINE:
			strncpy(buf, "\033[38;2;250;100;100m \u2699 \033[0m", buf_size);
			break;
		case STATE_MINE_MARKED:
			strncpy(buf, "\033[48;2;100;0;0m\033[38;2;250;100;100m \u2699 \033[0m", buf_size);
			break;
		case 0:
			strncpy(buf, "   ", buf_size);
			break;
		case 1:
			strncpy(buf, "\033[38;2;0;0;255m 1 \033[0m", buf_size);
			break;
		case 2:
			strncpy(buf, "\033[38;2;0;255;0m 2 \033[0m", buf_size);
			break;
		case 3:
			strncpy(buf, "\033[38;2;255;0;0m 3 \033[0m", buf_size);
			break;
		case 4:
			strncpy(buf, "\033[38;2;20;0;120m 4 \033[0m", buf_size);
			break;
		case 5:
			strncpy(buf, "\033[38;2;255;255;0m 5 \033[0m", buf_size);
			break;
		case 6:
			strncpy(buf, "\033[38;2;50;200;50m 6 \033[0m", buf_size);
			break;
		case 7:
			strncpy(buf, "\033[38;2;255;0;255m 7 \033[0m", buf_size);
			break;
		case 8:
			strncpy(buf, "\033[38;2;160;160;160m 8 \033[0m", buf_size);
			break;
	}
}

static void print_centered_3digit(unsigned i) {
	if (i < 10)
		printf(" %d ", i);
	else
		printf("%03d", i);
}

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

void print_board(const board* b, const board_geometry* g) {
	print_col_header(g);
	print_row_sep(g);
	for (unsigned row = 0; row < g->num_rows; ++row) {
		print_centered_3digit(row);
		printf(" |");
		for (unsigned col = 0; col < g->num_cols; ++col) {
			char state_str[64];
			get_state_char(b->state[get_index(row, col, g)], state_str, sizeof(state_str));
			printf("%s|", state_str);
		}
		printf(" ");
		print_centered_3digit(row);
		printf("\n");
		print_row_sep(g);
	}
	print_col_header(g);
}

static void print_won() {
	printf("You win!\n\n");
}

static void print_lost() {
	printf("You lose!\n\n");
}

static void query_restart(board* b, board_geometry* g) {
	printf("Start a new game? y/n\n");
	while (true) {
		char y_n;
		if (scanf(" %c", &y_n) != 1)
			continue;
		if (y_n == 'y' || y_n == 'Y') {
			init_board(b);
			print_board(b, g);
			handle_user_input(b, g);
		} else if (y_n == 'n' || y_n == 'N' || y_n == 'q' || y_n == 'Q')
			break;
	}
}

void handle_user_input(board* b, board_geometry* g) {
	bool won = false, lost = false, quit = false;
	while (true) {
		char action;

		if (scanf(" %c", &action) == 1) {
			bool help_required = false;
			int row, col;
			if ((action == 'a' || action == 'd' || action == 'r') && scanf("%d %d", &row, &col) == 2) {
				const unsigned board_index = get_index(row, col, g);
				switch (action) {
					case 'a':
						arm(b, board_index);
					break;
					case 'd':
						disarm(b, board_index);
					break;
					case 'r':
						lost = reveil(b, g, board_index);
					break;
				}
			} else if (action == 'q') {
				quit = true;
			} else
				help_required = true;

			if (help_required)
				print_game_help();
			else if (quit)
				break;
			else
				print_board(b, g);

			won = is_won(b);

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
