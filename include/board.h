#include <stdbool.h>

#include <util.h>
#include <geometry/command_line.h>
#include <geometry/geometry.h>

#ifndef INCLUDE_BOARD_H_
#define INCLUDE_BOARD_H_

#define STATE_HIDDEN -1
#define STATE_ARMED -2
#define STATE_MINE -3
#define STATE_MINE_MARKED -4
#define STATE_MINE_WON -5

typedef struct {
	unsigned num_tiles, num_mines;
	bool* mined;
	int* state;
	bool mines_placed;
} board;

error allocate_board(board** b, const board_geometry* g);
void free_board(board** b);

error init_board(board* b, const game_setup* setup);

unsigned count_armed(const board* b);

void arm(board* b, unsigned board_index);
void disarm(board* b, unsigned board_index);

bool is_won(board* b);

/*
 * @return true if the reveiled tile has a mine, false otherwise
 */
bool reveil(board* b, const board_geometry* g, unsigned board_index);

#endif
