#include "board.h"
#include "bitflags.h"
#include "sys/types.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Board gen_board(unsigned int cols, unsigned int rows) {
  Tile *tiles = malloc((cols * rows) * sizeof(Tile));
  memset(tiles, 0, (cols * rows) * sizeof(Tile));

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
    toggle_bomb(this, new_point(row, col));
  }
}

void place_tiles(Board *this) {
  for (unsigned int x = 0; x < this->num_rows; x++) {
    for (unsigned int y = 0; y < this->num_cols; y++) {
      if (check_bomb(board_get_tile(this, new_point(x, y)))) {
        continue;
      }

      unsigned int curr_tile_count = 0;

      for (int neighbor = Bottom; neighbor <= BRCorn; neighbor++) {
        if (check_bomb(
                board_get_neighboring(this, new_point(x, y), neighbor))) {
          curr_tile_count += 1;
        }
      }

      board_set_value(this, new_point(x, y), curr_tile_count);
    }
  }
}

Tile board_get_tile(Board *this, Point point) {
  // ensure that we are in bounds
  assert(point.x <= this->num_rows);
  assert(point.y <= this->num_cols);

  return this->tiles[this->num_cols * point.y + point.x];
}

void board_set_value(Board *this, Point point, u_int8_t new_val) {
  // ensure that we are in bounds
  assert(point.x <= this->num_rows);
  assert(point.y <= this->num_cols);

  this->tiles[this->num_cols * point.y + point.x].value = new_val;
}

void board_set_flags(Board *this, Point point, u_int8_t new_flags) {
  assert(point.x <= this->num_rows);
  assert(point.y <= this->num_cols);

  this->tiles[this->num_cols * point.y + point.x].flags = new_flags;
}
void print_board(Board *this) {
  for (unsigned x = 0; x < this->num_rows; x++) {
    for (unsigned y = 0; y < this->num_cols; y++) {
      Tile curr_tile = board_get_tile(this, new_point(x, y));
      if (true) {
        if (check_bomb(curr_tile))
          printf("*");
        else {
          printf("%d", curr_tile.value);
        }
      }
      else if (!check_flag(curr_tile)) {
         printf(" ");
      }
      if (check_flag(curr_tile)) {
          printf("$");
        }
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


static bool HAS_BEEN_CLICKED = false;

void board_dig(Board *this, Point point, bool flag) {
  /* ensure we are in bounds! */
  assert(point.x <= this->num_rows);
  assert(point.y <= this->num_cols);
  
  if (flag) {
    toggle_flag(this, point);
    printf("flagged: %d,%d \n", point.x, point.y);
  } else {
     // if you click a bomb, send the bomb to the top left corner, if that's occupied, send it to the right and repeat
    if (!HAS_BEEN_CLICKED && check_bomb(board_get_tile(this, point))) {
      unsigned int curr_x = 0;
      unsigned int curr_y = 0;
      Point curr_point = new_point(curr_x, curr_y);
      while (check_bomb(board_get_tile(this, curr_point))) {
         curr_x += 1;
         if (curr_x > this->num_rows) {
            curr_x = 0;
            curr_y += 1;
            curr_point = new_point(curr_x, curr_y);
         }
      }
         // swap bomb locations
         toggle_bomb(this, curr_point); 
         toggle_bomb(this, point);
         place_tiles(this); // regen map to accomidate for new bomb placements
      
    }

    set_reveal(this, point);
    printf("revealed: %d,%d \n", point.x, point.y);
    HAS_BEEN_CLICKED = true;
  }
}

Tile board_get_neighboring(Board *this, Point point, enum Neighbor flavor) {
  unsigned int x = point.x;
  unsigned int y = point.y;
  bool can_left = !(x == 0);
  bool can_right = !(x == this->num_rows);
  bool can_top = !(y == 0);
  bool can_bottom /* UwU */ = !(y == this->num_cols);

  Point neighboring;

  switch (flavor) {
  case Bottom: {
    if (can_bottom) {
      neighboring = new_point(x, y + 1);
    }
    break;
  }
  case Top: {
    if (can_top) {
      neighboring = new_point(x, y - 1);
    }
    break;
  }
  case Left: {
    if (can_left) {
      neighboring = new_point(x - 1, y);
    }
    break;
  }
  case Right: {
    if (can_right) {
      neighboring = new_point(x + 1, y);
    }
    break;
  }
  case TLCorn: {
    if (can_left && can_top) {
      neighboring = new_point(x - 1, y - 1);
    }
    break;
  }
  case TRCorn: {
    if (can_right && can_top) {
      neighboring = new_point(x + 1, y - 1);
    }
    break;
  }
  case BLCorn: {
    if (can_left && can_bottom) {
      neighboring = new_point(x - 1, y + 1);
    }
    break;
  }
  case BRCorn: {
    if (can_right && can_bottom) {
      neighboring = new_point(x + 1, y + 1);
    }
  }
  }
  if (neighboring.x == 0) {
    neighboring = new_point(x, y);
  }
  return board_get_tile(this, neighboring);
}
