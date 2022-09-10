#pragma once


#define BOMB_TILE 99

typedef struct {
   unsigned int num_rows;
   unsigned int num_cols;
   unsigned int *tiles;
} Board;

typedef struct {
   unsigned int x;
   unsigned int y;
} Point;



Point new_point(unsigned int x, unsigned int y);


Board gen_board(unsigned int cols, unsigned int rows);

unsigned int num_left(Board* this);

void place_mines(Board* this, unsigned int num_mines);
void place_tiles(Board* this);
unsigned int board_get(Board* this, Point point); // get tile in 2d position
void board_set(Board* this, Point point, unsigned int new_val); // set tile in 2d position
void print_board(Board* this);



void free_board(Board* this);


enum Neighbor {
   Bottom,
   Top,
   Left,
   Right,
   TLCorn,
   TRCorn,
   BLCorn,
   BRCorn
};
Point board_get_neighboring(Board *this, Point point, enum Neighbor flavor);
