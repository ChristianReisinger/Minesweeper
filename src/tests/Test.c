#include <stdio.h>
#include <stdbool.h>

#include <tests/board.h>

void test_report(char* test_name, unsigned* passed, unsigned* failed, bool success) {
	printf("%-30s ... ", test_name);
	if (success) {
		printf("success\n");
		++(*passed);
	} else {
		++(*failed);
		printf("failed\n");
	}
}

int main(int argc, char **argv) {
	printf("Running tests ...\n");

	unsigned passed = 0, failed = 0;
	test_report("init_board", &passed, &failed, test_init_board(12, 17, 23));
	test_report("place_mines", &passed, &failed, test_place_mines(12, 17, 23, 100000, 0.90));

	printf("%u tests run, %u passed, %u failed\n", passed + failed, passed, failed);
}
