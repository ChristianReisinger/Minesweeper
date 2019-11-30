#include <stdio.h>

#include <console_ui_rect.h>

char get_state_char(int state) {
	if (state == STATE_ARMED)
		return '!';
	else if (state == STATE_HIDDEN)
		return 'O';
	else if (state == STATE_MINE)
		return 'X';
	else if (state == STATE_MINE_MARKED)
		return '+';
	else if (state == 0)
		return ' ';
	else if (state > 0 && state < 9)
		return '0' + state;
	else
		return '?';
}

void print_board(const board* b, const board_geometry* g) {
	for (int row = 0; row < g->num_rows; ++row) {
		for (int col = 0; col < g->num_cols; ++col) {
			printf("%c", get_state_char(b->state[get_index(row, col, g)]));

		}
		printf("\n");
	}
}
