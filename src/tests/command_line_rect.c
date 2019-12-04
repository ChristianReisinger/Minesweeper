#include <defs.h>
#include <geometry.h>
#include <command_line_rect.h>

#include <tests/command_line_rect.h>

bool test_get_default_setup() {
	game_setup setup = get_default_setup();
	return (setup.num_rows == DEFAULT_ROW_NUM
			&& setup.num_cols == DEFAULT_COL_NUM
			&& setup.num_mines == DEFAULT_MINE_FRACTION * DEFAULT_ROW_NUM * DEFAULT_COL_NUM);
}
