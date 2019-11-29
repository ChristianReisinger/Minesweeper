#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#include <util.h>

unsigned random_unsigned_from_zero_to_max(unsigned max) {
	static bool rand_needs_init = true;
	if (rand_needs_init) {
		srand(time(NULL));
		rand_needs_init = false;
	}

	return max == 0 ? 0 : ((unsigned) rand()) % max;
}
