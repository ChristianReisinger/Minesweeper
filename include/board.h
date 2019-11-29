#include <stdbool.h>

#include <util.h>

#ifndef INCLUDE_BOARD_H_
#define INCLUDE_BOARD_H_

#define STATE_HIDDEN -1
#define STATE_ARMED -2
#define STATE_MINE -3
#define STATE_MINE_MARKED -4

typedef struct {
	unsigned num_tiles, num_mines;
	bool* mined;
	int* state;
} board;

/* forward declared */
typedef struct s_board_geometry board_geometry;
unsigned get_adjacent_mine_num(const board* b, const board_geometry* g, unsigned board_index);
/********************/

error allocate_board(board** b, unsigned num_tiles, unsigned num_mines);
void free_board(board** b);

error init_board(board* b);

void toggle_armed(board* b, unsigned board_index);

/*
 * @return true if the reveiled tile has a mine, false otherwise
 */
bool reveil(board* b, const board_geometry* g, unsigned board_index);

#endif
