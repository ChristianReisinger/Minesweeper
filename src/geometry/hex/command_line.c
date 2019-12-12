#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include <defs.h>
#include <geometry/hex/types.h>
#include <geometry/geometry.h>

#include <geometry/command_line.h>

static unsigned parse_natural_number(char* str) {
	char* end;
	int i = strtol(str, &end, 10);
	if (i <= 0) {
		printf("Invaild size '%d', exiting ...\n", i);
		exit(1);
	}
	return i;
}

error alloc_game_setup(game_setup** setup) {
	if ((*setup = (game_setup*) malloc(sizeof(game_setup))) == NULL)
		return MEMORY_ERR;

	return SUCCESS;
}

void free_game_setup(game_setup** setup) {
	if (*setup != NULL) {
		free(*setup);
		*setup = NULL;
	}
}

void print_program_help(char* argv0) {
	printf("Usage: %s [-h | --help]\n"
			"\t[(-r | --rows) <rows>] [(-c | --cols) <cols>]\n"
			"\t[(-m | --mines) <mines>]\n\n", argv0);
	exit(0);
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

void handle_GNU_options(int argc, char** argv, game_setup* setup) {
	static struct option long_opts[] = {
			{ "help", no_argument, 0, 'h' },
			{ "rows", required_argument, 0, 'r' },
			{ "cols", required_argument, 0, 'c' },
			{ "mines", required_argument, 0, 'm' },
			{ 0, 0, 0, 0 }
	};

	get_default_setup(setup);
	int opt = -1, long_opts_i = 0;
	while ((opt = getopt_long(argc, argv, "hr:c:m:", long_opts, &long_opts_i)) != -1) {
		switch (opt) {
			case 'h':
				print_program_help(argv[0]);
			break;
			case 'r':
				setup->num_rows = parse_natural_number(optarg);
			break;
			case 'c':
				setup->num_cols = parse_natural_number(optarg);
			break;
			case 'm':
				setup->num_mines = parse_natural_number(optarg);
			break;
		}
	}
	argv = argv + optind - 1;
}

void get_default_setup(game_setup* setup) {
	board_geometry* g;
	alloc_geometry(&g);
	init_default_geometry(g);

	setup->num_rows = g->num_rows;
	setup->num_cols = g->num_cols;
	setup->num_mines = DEFAULT_MINE_FRACTION * g->num_rows * g->num_cols;

	free_geometry(&g);
}

unsigned get_mine_num(const game_setup* setup) {
	return setup->num_mines;
}
