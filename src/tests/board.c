#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include <defs.h>
#include <board.h>
#include <geometry.h>

#include <tests/board.h>

bool test_init_board(unsigned num_mines) {
	board* b;
	board_geometry* g;
	if(alloc_default_geometry(&g) != SUCCESS)
		return false;

	unsigned num_tiles = get_tile_num(g);

	if(allocate_board(&b, g, num_mines) != SUCCESS)
		return false;
	if (init_board(b) != SUCCESS)
		return false;

	if (b->num_tiles != num_tiles || b->num_mines != num_mines)
		return false;

	unsigned placed_mines = 0;
	for (int i = 0; i < num_tiles; ++i) {
		if (b->mined[i])
			++placed_mines;
		if (b->state[i] != STATE_HIDDEN)
			return false;
	}
	if (placed_mines != num_mines)
		return false;

	free_board(&b);
	if (b != NULL)
		return false;

	return true;
}

bool test_place_mines(unsigned num_mines, unsigned num_runs, double allowed_relative_probability_deviation) {
	debug_print("Allocating geometry ...\n");
	board_geometry* g;
	if(alloc_default_geometry(&g) != SUCCESS)
		return false;

	unsigned num_tiles = get_tile_num(g);

	debug_print("Allocating board with %d tiles ...\n", num_tiles);
	board* b;
	if ((allocate_board(&b, g, num_mines)) != SUCCESS)
		return false;

	unsigned total_placed_mines[num_tiles];
	for (int i = 0; i < num_tiles; ++i)
		total_placed_mines[i] = 0;

	debug_print("Sampling average number of placed mines ...\n");
	for (int n = 0; n < num_runs; ++n) {
		init_board(b);
		for (int i = 0; i < num_tiles; ++i)
			if (b->mined[i])
				++total_placed_mines[i];
	}

	debug_print("Verifying probability distribution ...\n");
	const double expected_avg_mines = ((double) num_mines / num_tiles);
	for (int i = 0; i < num_tiles; ++i) {
		const double avg_mines = ((double) total_placed_mines[i] / num_runs);
		if (avg_mines < expected_avg_mines * (1 - allowed_relative_probability_deviation)
				|| avg_mines > expected_avg_mines * (1 + allowed_relative_probability_deviation))
			return false;
	}

	return true;
}
