#include <stdio.h>
#include <stdbool.h>

#include <tests/util.h>
#include <tests/board.h>

void report_status(char* test_name) {
	printf("%-40s ... ", test_name);
	fflush(stdout);
}

void report_result(unsigned* passed, unsigned* failed, bool success) {
	if (success) {
		++(*passed);
		printf("success\n");
	} else {
		++(*failed);
		printf("failed\n");
	}
	fflush(stdout);
}

int main(int argc, char** argv) {
	printf("Running tests ...\n");

	unsigned passed = 0, failed = 0;
	report_status("random_unsinged_from_zero_to_max");
	report_result(&passed, &failed, test_random_unsigned_from_zero_to_max(100, 500000, 0.05));
	report_status("init_board");
	report_result(&passed, &failed, test_init_board(23));
	report_status("place_mines");
	report_result(&passed, &failed, test_place_mines(23, 200000, 0.05));

	printf("%u tests run, %u passed, %u failed\n", passed + failed, passed, failed);
}
