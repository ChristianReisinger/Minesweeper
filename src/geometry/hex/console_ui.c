#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <console_ui/formatting.h>
#include <geometry/command_line.h>
#include <geometry/hex/types.h>
#include <geometry/hex/shared_detail.h>

#include <geometry/console_ui.h>

static void print_col_header(const board_geometry* g) {
	printf("    ");
	for (unsigned col = 0; col < g->num_cols; ++col) {
		printf(" ");
		print_centered_3digit(col);
	}
	printf("\n");
}

unsigned get_ui_width(const board_geometry* g) {
	return 10 + 4 * g->num_cols;
}

void print_board(const board* b, const board_geometry* g) {
	bool even_cols = g->num_cols % 2 == 0;

	print_col_header(g);

	printf("    ");
	for (unsigned col = 0; col < g->num_cols; ++col)
		printf(" %s", col % 2 == 0 ? "___" : "   ");

	for (unsigned row = 0; row < g->num_rows; ++row) {
		printf("\n");
		print_centered_3digit(row);
		printf(" ");

		char state_str[64];
		for (unsigned col = 0; col < g->num_cols; ++col) {
			if (col % 2 == 0) {
				get_state_string(b->state[get_index(row, col, g)], state_str, sizeof(state_str));
				printf("/%s\\", state_str);
			} else
				printf("___");
		}
		if (even_cols) {
			if (row != 0)
				printf("/");
			else
				printf(" ");
		}

		printf(" ");
		print_centered_3digit(row);

		printf("\n    \\");
		for (unsigned col = 0; col < g->num_cols; ++col) {
			if (col % 2 == 0)
				printf("___/");
			else {
				get_state_string(b->state[get_index(row, col, g)], state_str, sizeof(state_str));
				printf("%s\\", state_str);
			}
		}

	}
	printf("\n     ");
	for (unsigned col = 0; col < g->num_cols; ++col) {
		if (col % 2 == 0)
			printf("   ");
		else
			printf("\\___/");
	}
	printf("\n");
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
