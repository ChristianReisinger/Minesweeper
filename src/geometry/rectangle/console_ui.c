#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <console_ui/formatting.h>
#include <geometry/command_line.h>
#include <geometry/rectangle/types.h>
#include <geometry/rectangle/shared_detail.h>

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

unsigned get_ui_width(const board_geometry* g) {
	return 10 + 4 * g->num_cols;
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

bool read_board_index(unsigned* board_index, const board_geometry* g) {
	int row, col;
	if (scanf("%d %d", &row, &col) == 2) {
		*board_index = get_index(row, col, g);
		return true;
	}
	return false;
}
