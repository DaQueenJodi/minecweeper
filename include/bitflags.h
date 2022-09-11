#pragma once
#include "board.h"
#include <stdbool.h>

extern const unsigned int FLAG;
extern const unsigned int BOMB;
extern const unsigned int REVEALED;

void toggle_flag(Board *board, Point point);
void toggle_bomb(Board *board, Point point);
void set_reveal(Board *board, Point point);
bool check_flag(Tile);
bool check_bomb(Tile);
bool check_reveal(Tile);
