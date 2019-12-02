#include <stdio.h>
#include <string.h>

#include <console_ui_rect.h>

static void get_state_char(int state, char* buf, unsigned buf_size) {
	if (buf == NULL || buf_size < 4)
		return;

	if (state == STATE_ARMED)
		strncpy(buf, " ! ", buf_size);
	else if (state == STATE_HIDDEN)
		strncpy(buf, " # ", buf_size);
	else if (state == STATE_MINE)
		strncpy(buf, " X ", buf_size);
	else if (state == STATE_MINE_MARKED)
		strncpy(buf, " + ", buf_size);
	else if (state == 0)
		strncpy(buf, "   ", buf_size);
	else if (state > 0 && state < 9) {
		strncpy(buf, "   ", buf_size);
		buf[1] = '0' + state;
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
			char state_str[4];
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
