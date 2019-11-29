#include <stddef.h>
#include <math.h>

#include <board.h>

#include <tests/board.h>

bool test_init_board(unsigned num_rows, unsigned num_cols, unsigned num_mines) {
	board_error err;

	board* b;
	err = allocate_board(&b, num_rows, num_cols, num_mines);
	err = init_board(b);
	if (err != SUCCESS)
		return false;

	if (b->num_rows != num_rows || b->num_cols != num_cols || b->num_mines != num_mines)
		return false;

	unsigned placed_mines = 0;
	for (int i = 0; i < num_rows * num_cols; ++i) {
		if (b->mined[i])
			++placed_mines;
		if (b->state[i] != HIDDEN)
			return false;
	}
	if (placed_mines != num_mines)
		return false;

	free_board(&b);
	if (b != NULL)
		return false;

	return true;
}

bool test_place_mines(unsigned num_rows, unsigned num_cols, unsigned num_mines, unsigned num_runs,
		double min_fraction_within_2sigma) {
	board* b;
	if ((allocate_board(&b, num_rows, num_cols, num_mines)) != SUCCESS)
		return false;

	unsigned total_placed_mines[num_rows * num_cols];
	for (int i = 0; i < num_rows * num_cols; ++i)
		total_placed_mines[i] = 0;

	for (int n = 0; n < num_runs; ++n) {
		init_board(b);
		for (int i = 0; i < num_rows * num_cols; ++i) {
			if (b->mined[i])
				++total_placed_mines[i];
		}
	}

	const double expected_avg_mines = ((double) num_mines / (num_rows * num_cols));
	double sigma = 0.0;
	for (int i = 0; i < num_rows * num_cols; ++i) {
		const double avg_mines = ((double) total_placed_mines[i] / num_runs);
		sigma += (avg_mines - expected_avg_mines) * (avg_mines - expected_avg_mines);
	}
	sigma = sqrt(sigma / num_runs);

	unsigned samples_within_2sigma = 0;
	for (int i = 0; i < num_rows * num_cols; ++i) {
		const double avg_mines = ((double) total_placed_mines[i] / num_runs);
		if(avg_mines > expected_avg_mines - 2*sigma && avg_mines < expected_avg_mines + 2*sigma)
			++samples_within_2sigma;
	}

	return ((double) samples_within_2sigma) / (num_rows * num_cols) >= min_fraction_within_2sigma;
}
