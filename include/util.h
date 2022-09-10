#pragma once
#include <stdlib.h>
#include <stdbool.h>

enum Mode {
   Easy,
   Hard,
   Medium,
   Custom
};

typedef struct {
  unsigned int row;
  unsigned int col;
  bool flag;
} BoardInput;



typedef struct {
  unsigned int capacity;
  char *buff;
  unsigned int length;
} String;

String new_string();
void free_string(String* s);
void string_append(String *this, char c);
String prompt(char* string);
void mode_prompt(enum Mode *mode, int *rows, int *cols);
String read_till_space(String input, unsigned int offset);
BoardInput parse_input(String input);
