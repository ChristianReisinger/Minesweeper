#include <board.h>
#include <geometry.h>

#ifndef INCLUDE_CONSOLE_UI_H_
#define INCLUDE_CONSOLE_UI_H_

void print_board(const board* b, const board_geometry* g);
void handle_user_input(board* b, board_geometry* g);

#endif
