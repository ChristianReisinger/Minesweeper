#ifndef INCLUDE_COMMAND_LINE_C_
#define INCLUDE_COMMAND_LINE_C_

typedef struct {
	unsigned num_rows;
	unsigned num_cols;
	unsigned num_mines;
} game_setup;

void print_program_help(char* argv0);
void print_game_help();
game_setup handle_GNU_options(int argc, char** argv);

#endif
