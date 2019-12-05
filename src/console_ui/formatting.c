#include <stdio.h>
#include <string.h>

#include <board.h>

#include <console_ui/formatting.h>

void get_state_char(int state, char* buf, unsigned buf_size) {
	if (buf == NULL || buf_size < 64)
		return;

	switch (state) {
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
		case STATE_MINE_WON:
			strncpy(buf, "\033[48;2;0;120;0m\033[38;2;250;100;100m \u2699 \033[0m", buf_size);
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
			strncpy(buf, "\033[38;2;30;0;140m 4 \033[0m", buf_size);
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

void print_centered_3digit(unsigned i) {
	if (i < 10)
		printf(" %d ", i);
	else
		printf("%3d", i);
}
