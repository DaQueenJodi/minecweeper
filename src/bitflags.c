#include "bitflags.h"
#include "board.h"

const unsigned int FLAG = 0x1;
const unsigned int BOMB = 0x2;
const unsigned int REVEALED = 0x4;
void toggle_flag(Board *board, Point point) {
   Tile tile = board_get_tile(board, point);
   unsigned int new = tile.flags ^ FLAG;  
   board_set_flags(board, point, new); 
}

void toggle_bomb(Board *board, Point point) {
   Tile tile = board_get_tile(board, point);
   unsigned int new = tile.flags ^ BOMB;
   board_set_flags(board, point, new);
}

void set_reveal(Board *board, Point point) {
   Tile tile = board_get_tile(board, point);
   unsigned int new = tile.flags | REVEALED;
   board_set_flags(board, point, new);
}
bool check_flag(Tile tile) {
   return (tile.flags  & FLAG) == FLAG;
}
bool check_bomb(Tile tile) {
   return (tile.flags  & BOMB) == BOMB;
}
bool check_reveal(Tile tile) {
   return (tile.flags & REVEALED) == REVEALED;
}
