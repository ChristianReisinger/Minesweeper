#include <stdio.h>
#include <getopt.h>

#include <command_line.h>

void print_program_help(char* argv0) {
	printf("Usage: %s\n\n", argv0);
}

void print_game_help() {
	printf("Possible user input:\n"
			"\t%-15s : reveal tile at (row,col)\n"
			"\t%-15s : arm tile at (row,col)\n"
			"\t%-15s : disarm tile at (row,col)\n"
			"\t%-15s : print this help text\n"
			"\t%-15s : quit the game\n"
			"r on an already reveiled tile reveils adjacent tiles if it is safe!\n\n",
			"r row col", "a row col", "d row col", "h", "q");
}

void handle_GNU_options(int argc, char** argv) {
	static struct option long_opts[] = {
			{ "help", no_argument, 0, 'h' },
			{ 0, 0, 0, 0 }
	};

	int opt = -1, long_opts_i = 0;
	while ((opt = getopt_long(argc, argv, "h", long_opts, &long_opts_i)) != -1) {
		switch (opt) {
			case 'h':
				print_program_help(argv[0]);
			break;
		}
	}
	argv = argv + optind - 1;
}
