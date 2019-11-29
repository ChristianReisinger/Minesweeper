#ifndef INCLUDE_TESTS_BOARD_H_
#define INCLUDE_TESTS_BOARD_H_

bool test_init_board(unsigned num_rows, unsigned num_cols, unsigned num_mines);
bool test_place_mines(unsigned num_rows, unsigned num_cols, unsigned num_mines, unsigned num_runs,
		double min_fraction_within_2sigma);

#endif
