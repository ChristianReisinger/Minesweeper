#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include <defs.h>
#include <board.h>
#include <geometry/geometry.h>
#include <geometry/command_line.h>

#include <tests/board.h>

bool test_init_board() {
	debug_print("Creating setup ...\n");
	game_setup* setup;
	if (alloc_game_setup(&setup) != SUCCESS)
		return false;
	get_default_setup(setup);
	const unsigned num_mines = get_mine_num(setup);

	debug_print("Creating geometry ...\n");
	board_geometry* g;
	if (alloc_geometry(&g) != SUCCESS || init_default_geometry(g) != SUCCESS)
		return false;

	unsigned num_tiles = get_tile_num(g);

	debug_print("Creating board ...\n");
	board* b;
	if (allocate_board(&b, g) != SUCCESS || init_board(b, setup) != SUCCESS)
		return false;

	for (unsigned i = 0; i < num_tiles; ++i)
		if (b->mined[i] || b->state[i] != STATE_HIDDEN)
			return false;

	if (b->num_tiles != num_tiles || b->num_mines != num_mines || b->mines_placed)
		return false;

	free_board(&b);
	free_geometry(&g);
	free_game_setup(&setup);
	if (b != NULL || g != NULL || setup != NULL)
		return false;

	return true;
}

bool test_place_mines(unsigned num_runs, double allowed_relative_probability_deviation) {
	debug_print("Allocating game_setup ...\n");
	game_setup* setup;
	if (alloc_game_setup(&setup) != SUCCESS)
		return false;
	get_default_setup(setup);
	const unsigned num_mines = get_mine_num(setup);

	debug_print("Allocating geometry ...\n");
	board_geometry* g;
	if (alloc_geometry(&g) != SUCCESS || init_default_geometry(g) != SUCCESS)
		return false;

	unsigned num_tiles = get_tile_num(g);

	debug_print("Allocating board with %d tiles ...\n", num_tiles);
	board* b;
	if ((allocate_board(&b, g)) != SUCCESS || init_board(b, setup) != SUCCESS)
		return false;

	debug_print("Verifying mine number ...\n");
	reveil(b, g, 0);
	unsigned placed_mines = 0;
	for (unsigned i = 0; i < num_tiles; ++i)
		if (b->mined[i])
			++placed_mines;
	if (placed_mines != num_mines)
		return false;

	unsigned total_placed_mines[num_tiles];
	for (unsigned i = 0; i < num_tiles; ++i)
		total_placed_mines[i] = 0;

	debug_print("Sampling average number of placed mines ...\n");
	for (unsigned n = 0; n < num_runs; ++n) {
		init_board(b, setup);
		reveil(b, g, 0); /* (x) board_index = 0 will never have a mine ! */
		for (unsigned i = 0; i < num_tiles; ++i)
			if (b->mined[i])
				++total_placed_mines[i];
	}

	debug_print("Verifying probability distribution ...\n");
	const double expected_avg_mines = ((double) num_mines / (num_tiles - 1.0)); /* (x) */
	for (unsigned i = 1; i < num_tiles; ++i) { /* (x) */
		const double avg_mines = ((double) total_placed_mines[i] / num_runs);
		if (avg_mines < expected_avg_mines * (1 - allowed_relative_probability_deviation)
				|| avg_mines > expected_avg_mines * (1 + allowed_relative_probability_deviation))
			return false;
	}

	free_board(&b);
	free_geometry(&g);
	free_game_setup(&setup);
	if (b != NULL || g != NULL || setup != NULL)
		return false;

	return true;
}
