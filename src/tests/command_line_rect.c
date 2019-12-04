#include <defs.h>
#include <geometry.h>
#include <geometry/rectangle/types.h>
#include <command_line_rect.h>

#include <util.h>
#include <tests/command_line_rect.h>

bool test_get_default_setup() {
	board_geometry* g;
	if(alloc_default_geometry(&g) != SUCCESS)
		return false;

	game_setup setup = get_default_setup();
	bool success = setup.num_rows == g->num_rows
			&& setup.num_cols == g->num_cols
			&& setup.num_mines == DEFAULT_MINE_FRACTION * g->num_rows * g->num_cols;

	free_geometry(&g);

	return success;
}
