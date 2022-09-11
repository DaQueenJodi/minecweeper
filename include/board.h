#pragma once

#include <stdbool.h>
#include <sys/types.h>
typedef struct {
  unsigned int x;
  unsigned int y;
} Point;

typedef struct {
 u_int8_t flags : 4;
  u_int8_t value : 4;
} Tile;

typedef struct {
  unsigned int num_rows;
  unsigned int num_cols;
  Tile *tiles;
} Board;

Point new_point(unsigned int x, unsigned int y);

Board gen_board(unsigned int cols, unsigned int rows);

unsigned int num_left(Board *this);

void place_mines(Board *this, unsigned int num_mines);
void place_tiles(Board *this);
Tile board_get_tile(Board *this, Point point); // get tile in 2d position
void board_set_value(Board *this, Point point, u_int8_t new_val);
void board_set_flags(Board *this, Point point, u_int8_t new_flags);
void print_board(Board *this);

void free_board(Board *this);

enum Neighbor { Bottom, Top, Left, Right, TLCorn, TRCorn, BLCorn, BRCorn };
Tile board_get_neighboring(Board *this, Point point, enum Neighbor flavor);



void board_dig(Board *this, Point point, bool flag);
