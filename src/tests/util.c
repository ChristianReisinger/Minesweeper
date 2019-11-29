#include <math.h>

#include <util.h>

#include <tests/util.h>

test_random_unsigned_from_zero_to_max(unsigned max, unsigned num_draws) {
	for (unsigned curr_max = 0; curr_max <= max; ++curr_max) {

		unsigned draws[curr_max + 1];
		for (int i = 0; i <= curr_max; ++i)
			draws[i] = 0;

		for (unsigned i = 0; i < num_draws; ++i)
			++draws[random_unsigned_from_zero_to_max(curr_max)];

		double sigma = 0.0;
		double expected_draws = (1.0 / (curr_max + 1));
		for (int i = 0; i <= curr_max; ++i) {
			const unsigned avg_draws = ((double) draws[i]) / (curr_max + 1);
			sigma += (avg_draws - expected_draws) * (avg_draws - expected_draws);
		}
		sigma = sqrt(sigma / (curr_max + 1));

	}
}
