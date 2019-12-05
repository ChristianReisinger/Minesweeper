#include <util.h>

#ifndef INCLUDE_GEOMETRY_COMMAND_LINE_C_
#define INCLUDE_GEOMETRY_COMMAND_LINE_C_

typedef struct game_setup game_setup;

error alloc_game_setup(game_setup** setup);
void free_game_setup(game_setup** setup);

void print_program_help(char* argv0);
void print_game_help();
void handle_GNU_options(int argc, char** argv, game_setup* setup);
void get_default_setup(game_setup* setup);
unsigned get_mine_num(game_setup* setup);

#endif
