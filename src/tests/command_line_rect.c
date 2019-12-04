#include <defs.h>
#include <geometry.h>
#include <command_line_rect.h>

#include <tests/command_line_rect.h>

bool test_get_default_setup() {
	board_geometry g = get_default_geometry();
	game_setup setup = get_default_setup();
	return (setup.num_rows == g.num_rows
			&& setup.num_cols == g.num_cols
			&& setup.num_mines == DEFAULT_MINE_FRACTION * g.num_rows * g.num_cols);
}
