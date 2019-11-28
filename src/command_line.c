#include <stdio.h>
#include <getopt.h>

#include <command_line.h>

void print_help(char* argv0) {
	fprintf(stderr, "Usage: %s", argv0);
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
				print_help();
			break;
		}
	}
	argv = argv + optind - 1;
}
