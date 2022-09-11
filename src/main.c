#include "bitflags.h"
#include "board.h"
#include "util.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
void do_input(Board *board, BoardInput input);

int main() {

  bool running = true;
  enum Mode mode;
  srand(time(NULL));
  Board board;
  board = gen_board(5, 5);
  while (running) { // MAIN LOOP
    print_board(&board);
    String input = prompt("do the do: \n");
    BoardInput board_input = parse_input(input);
    do_input(&board, board_input);
  }
  free_board(&board);
}

// INPUT FORMAT: x(x) y(y) [!] ex: 23 15 f
void do_input(Board *board, BoardInput input) {
  if (input.col > board->num_cols || input.row > board->num_rows) {
    return; // return early
  }
   
  Point point = new_point(input.row, input.col);
  board_dig(board, point, input.flag);
}
