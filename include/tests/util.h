#include <stdbool.h>

#ifndef INCLUDE_TESTS_UTIL_H_
#define INCLUDE_TESTS_UTIL_H_

bool test_random_unsigned_from_zero_to_max(unsigned max, unsigned num_draws, double allowed_relative_probability_deviation);

#endif
