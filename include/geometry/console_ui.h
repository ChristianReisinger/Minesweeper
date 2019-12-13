#include <stdbool.h>
#include <time.h>

#include <board.h>
#include <geometry/geometry.h>

#ifndef INCLUDE_GEOMETRY_CONSOLE_UI_H_
#define INCLUDE_GEOMETRY_CONSOLE_UI_H_

unsigned get_ui_width(const board_geometry* g);
void print_board(const board* b, const board_geometry* g);
bool handle_action(bool* lost, board* b, const board_geometry* g, char action); //TODO make only coordinate parsing geometry-specific and put into more general header

#endif
