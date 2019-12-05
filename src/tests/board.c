#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include <defs.h>
#include <board.h>
#include <geometry/geometry.h>
#include <geometry/command_line.h>

#include <tests/board.h>

static bool create_setup(game_setup** setup) {
	debug_print("Creating setup ... ");
	if (alloc_game_setup(setup) != SUCCESS)
		return false;
	get_default_setup(*setup);
	debug_print("o.k.\n");
	return true;
}

static bool create_geometry(board_geometry** g) {
	debug_print("Creating geometry ... ");
	if (alloc_geometry(g) != SUCCESS || init_default_geometry(*g) != SUCCESS)
		return false;
	debug_print("o.k.\n");
	return true;
}

static bool create_board(board** b, const board_geometry* g, const game_setup* setup) {
	debug_print("Creating board with %d tiles ... ", get_tile_num(g));
	if (allocate_board(b, g) != SUCCESS || init_board(*b, setup) != SUCCESS)
		return false;
	debug_print("o.k.\n");
	return true;
}

bool test_init_board() {
	game_setup* setup;
	board_geometry* g;
	board* b;

	if (!create_setup(&setup)
			|| !create_geometry(&g)
			|| !create_board(&b, g, setup))
		return false;

	debug_print("Verifying board ... ");
	if (b->num_tiles != get_tile_num(g) || b->num_mines != get_mine_num(setup) || b->mines_placed)
		return false;

	for (unsigned i = 0; i < get_tile_num(g); ++i)
		if (b->mined[i] || b->state[i] != STATE_HIDDEN)
			return false;
	debug_print("o.k.\n");

	free_board(&b);
	free_geometry(&g);
	free_game_setup(&setup);
	if (b != NULL || g != NULL || setup != NULL)
		return false;

	return true;
}

bool test_place_mines(unsigned num_runs, double allowed_relative_probability_deviation) {
	game_setup* setup;
	board_geometry* g;
	board* b;

	if (!create_setup(&setup)
			|| !create_geometry(&g)
			|| !create_board(&b, g, setup))
		return false;

	const unsigned num_tiles = get_tile_num(g);
	const unsigned num_mines = get_mine_num(setup);

	debug_print("Verifying mine number ... ");
	reveil(b, g, 0);
	unsigned placed_mines = 0;
	for (unsigned i = 0; i < num_tiles; ++i)
		if (b->mined[i])
			++placed_mines;
	if (placed_mines != num_mines)
		return false;
	debug_print("o.k.\n");

	unsigned total_placed_mines[num_tiles];
	for (unsigned i = 0; i < num_tiles; ++i)
		total_placed_mines[i] = 0;

	debug_print("Sampling average number of placed mines ... ");
	for (unsigned n = 0; n < num_runs; ++n) {
		init_board(b, setup);
		reveil(b, g, 0); /* (x) board_index = 0 will never have a mine ! */
		for (unsigned i = 0; i < num_tiles; ++i)
			if (b->mined[i])
				++total_placed_mines[i];
	}
	debug_print("o.k.\n");

	debug_print("Total mines placed: ");
	for (unsigned i = 0; i < num_tiles; ++i)
		debug_print("%d ", total_placed_mines[i]);
	debug_print("\n");

	debug_print("Verifying probability distribution ... ");
	const double expected_avg_mines = ((double) num_mines / (num_tiles - 1.0)); /* (x) */
	for (unsigned i = 1; i < num_tiles; ++i) { /* (x) */
		const double avg_mines = ((double) total_placed_mines[i] / num_runs);
		if (avg_mines < expected_avg_mines * (1 - allowed_relative_probability_deviation)
				|| avg_mines > expected_avg_mines * (1 + allowed_relative_probability_deviation)) {
			debug_print("unexpected probability at tile %u: %lf, expected %lf\n", i, avg_mines, expected_avg_mines);
			return false;
		}
	}
	debug_print("o.k.\n");

	free_board(&b);
	free_geometry(&g);
	free_game_setup(&setup);
	if (b != NULL || g != NULL || setup != NULL)
		return false;

	return true;
}
