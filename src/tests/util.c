#include <math.h>

#include <util.h>

#include <tests/util.h>

bool test_random_unsigned_from_zero_to_max(unsigned max, unsigned num_draws, double allowed_relative_probability_deviation) {
	unsigned draws[max + 1];
	for (int i = 0; i <= max; ++i)
		draws[i] = 0;

	for (unsigned i = 0; i <= num_draws; ++i)
		++draws[random_unsigned_from_zero_to_max(max)];

	double expected_avg_draws = (1.0 / (max + 1));
	for (int i = 0; i <= max; ++i) {
		const double avg_draws = ((double) draws[i]) / num_draws;
		if (avg_draws < expected_avg_draws * (1 - allowed_relative_probability_deviation) ||
				avg_draws > expected_avg_draws * (1 + allowed_relative_probability_deviation))
			return false;
	}
	return true;
}
