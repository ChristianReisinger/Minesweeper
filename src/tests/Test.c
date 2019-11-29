#include <stdio.h>

#include <tests/board.h>

int main(int argc, char **argv) {
	printf("Running tests ...\n");

	unsigned passed = 0, failed = 0;
	test_init_board(12, 17, 23) ? ++passed : ++failed;
	test_place_mines(12, 17, 23, 500000, 0.9) ? ++passed : ++failed;

	printf("%u tests run, %u passed, %u failed\n", passed + failed, passed, failed);
}
