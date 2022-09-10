#include "board.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Board gen_board(unsigned int cols, unsigned int rows) {
  unsigned int *tiles = malloc((cols * rows) * sizeof(unsigned int));
  memset(tiles, 0, (cols * rows) * sizeof(int));

  Board board;
  board.tiles = tiles;

  board.num_cols = cols - 1;
  board.num_rows = rows - 1;
  place_mines(&board, 3);
  place_tiles(&board);
  return board;
}

void place_mines(Board *this, unsigned int num_mines) {
  for (unsigned int i = 0; i < num_mines; i++) {
    unsigned int row = rand() % this->num_rows;
    unsigned int col = rand() % this->num_cols;
    board_set(this, new_point(row, col), BOMB_TILE);
  }
}

void place_tiles(Board *this) {
  for (unsigned int x = 0; x < this->num_rows; x++) {
    for (unsigned int y = 0; y < this->num_cols; y++) {
      if (board_get(this, new_point(x, y)) == BOMB_TILE) {
        continue;
      }

      unsigned int curr_tile_count = 0;

      for (int neighbor = Bottom; neighbor <= BRCorn; neighbor++) {
        if (board_get(this, board_get_neighboring(this, new_point(x, y),
                                                  neighbor)) == BOMB_TILE) {
          curr_tile_count += 1;
        }
      }

      board_set(this, new_point(x, y), curr_tile_count);
    }
  }
}

unsigned int board_get(Board *this, Point point) {
  // ensure that we are in bounds
  assert(point.x <= this->num_rows);
  assert(point.y <= this->num_cols);

  return this->tiles[this->num_cols * point.y + point.x];
}

void board_set(Board *this, Point point, unsigned int new_val) {
  // ensure that we are in bounds
  assert(point.x <= this->num_rows);
  assert(point.y <= this->num_cols);

  this->tiles[this->num_cols * point.y + point.x] = new_val;
}

void print_board(Board *this) {
  for (unsigned x = 0; x < this->num_rows; x++) {
    for (unsigned y = 0; y < this->num_cols; y++) {
      unsigned int curr_tile = board_get(this, new_point(x, y));
      if (curr_tile == BOMB_TILE)
        printf("*");
      else {
        printf("%d", curr_tile);
      }
      printf(" ");
    }
    printf("\n");
  }
}

Point new_point(unsigned int x, unsigned int y) {
  Point point;
  point.x = x;
  point.y = y;
  return point;
}

void free_board(Board *this) { free(this->tiles); }

void board_dig(Board *this, Point point, bool flag) {
  /* ensure we are in bounds! */
  assert(point.x <= this->num_rows);
  assert(point.y <= this->num_cols);

//board_get(this, );
}

Point board_get_neighboring(Board *this, Point point, enum Neighbor flavor) {
  unsigned int x = point.x;
  unsigned int y = point.y;
  bool can_left = !(x == 0);
  bool can_right = !(x == this->num_rows);
  bool can_top = !(y == 0);
  bool can_bottom /* UwU */ = !(y == this->num_cols);

  switch (flavor) {
  case Bottom: {
    if (can_bottom) {
      return new_point(x, y + 1);
    }
    break;
  }
  case Top: {
    if (can_top) {
      return new_point(x, y - 1);
    }
    break;
  }
  case Left: {
    if (can_left) {
      return new_point(x - 1, y);
    }
    break;
  }
  case Right: {
    if (can_right) {
      return new_point(x + 1, y);
    }
  }
  case TLCorn: {
    if (can_left && can_top) {
      return new_point(x - 1, y - 1);
    }
    break;
  }
  case TRCorn: {
    if (can_right && can_top) {
      return new_point(x + 1, y - 1);
    }
    break;
  }
  case BLCorn: {
    if (can_left && can_bottom) {
      return new_point(x - 1, y + 1);
    }
    break;
  }
  case BRCorn: {
    if (can_right && can_bottom) {
      return new_point(x + 1, y + 1);
    }
  }
  }

  return new_point(x, y); // otherwise just return itself
}
