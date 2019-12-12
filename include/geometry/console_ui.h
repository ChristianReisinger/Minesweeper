#include <stdbool.h>
#include <time.h>

#include <board.h>
#include <geometry/geometry.h>

#ifndef INCLUDE_GEOMETRY_CONSOLE_UI_H_
#define INCLUDE_GEOMETRY_CONSOLE_UI_H_

void print_header(const board* b, const board_geometry* g, const time_t game_start_time); //TODO pass width instead of geometry and put into more general header
void print_board(const board* b, const board_geometry* g);
bool handle_action(bool* lost, board* b, const board_geometry* g, char action); //TODO make only coordinate parsing geometry-specific and put into more general header

#endif
