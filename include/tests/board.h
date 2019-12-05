#include <stdbool.h>

#ifndef INCLUDE_TESTS_BOARD_H_
#define INCLUDE_TESTS_BOARD_H_

bool test_init_board();
bool test_place_mines(unsigned num_runs, double allowed_relative_probability_deviation);

#endif
