#include <stdbool.h>
#include <time.h>

#include <board.h>
#include <geometry/geometry.h>

#ifndef INCLUDE_GEOMETRY_CONSOLE_UI_H_
#define INCLUDE_GEOMETRY_CONSOLE_UI_H_

unsigned get_ui_width(const board_geometry* g);
void print_board(const board* b, const board_geometry* g);
bool read_board_index(unsigned* board_index, const board_geometry* g);

#endif
