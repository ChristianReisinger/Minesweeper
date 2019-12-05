#include <defs.h>
#include <geometry/command_line.h>
#include <geometry/rectangle/types.h>
#include <geometry/geometry.h>
#include <util.h>

#include <tests/command_line_rect.h>

bool test_get_default_setup() {
	game_setup* setup;
	alloc_game_setup(&setup);
	get_default_setup(setup);

	board_geometry* g;
	if(alloc_default_geometry(&g) != SUCCESS)
		return false;

	bool success = setup->num_rows == g->num_rows
			&& setup->num_cols == g->num_cols
			&& setup->num_mines == DEFAULT_MINE_FRACTION * g->num_rows * g->num_cols;

	free_geometry(&g);
	free_game_setup(&setup);

	return success;
}
