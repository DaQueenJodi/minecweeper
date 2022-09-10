#include "util.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
String new_string() {
  String s;
  s.buff = malloc(5 * sizeof(char));
  s.capacity = 5 * sizeof(char);
  s.length = 0;

  memset(s.buff, 0, s.capacity);

  return s;
}

void string_append(String *this, char c) {
  if (this->length == this->capacity) {
    this->capacity += 5;
    this->buff = realloc(this->buff, this->capacity);
  }
  this->buff[this->length] = c;
  this->length += 1;
}

// returns length
String read_line() {
  String s = new_string();
  char curr_char = 0;
  while (curr_char != '\n') { // until end of line
    curr_char = getc(stdin);
    string_append(&s, curr_char);
  }
  return s;
}

String prompt(char *string) {
  printf("%s", string);
  return read_line();
}

void mode_prompt(enum Mode *mode, int *rows, int *cols) {
  while (!mode && !rows && !cols) {
    if (mode == NULL) {
      printf("Select a game mode: \n");
      String input = prompt("[E]asy, [M]edium, [H]ard, [C]ustom \n");

      switch (tolower(input.buff[0])) {
      case 'e':
        *mode = Easy;
        break;
      case 'm':
        *mode = Medium;
        break;
      case 'h':
        *mode = Hard;
        break;
      case 'c':
        *mode = Custom;
        break;
      default:
        printf("Please pick a valid prompt! \n");
      }
      free_string(&input);
      continue;
    }
    if (*rows < 1) {
      switch (*mode) {
      case Easy:
        *rows = 9;
        break;
      case Medium:
        *rows = 16;
        break;
      case Hard:
        *rows = 30;
        break;
      case Custom: {
        String input = prompt("Enter the number of rows: ");
        *rows = atoi(input.buff);
        free_string(&input);
        break;
      }

        continue;
      }
    }
    if (*cols < 1) {
      switch (*mode) {
      case Easy:
        *cols = 9;
        break;
      case Medium:
        *cols = 16;
        break;
      case Hard:
        *cols = 16;
        break;
      case Custom: {
        String input = prompt("Enter the number of cols: ");
        *rows = atoi(input.buff);
        free_string(&input);
        break;
      }
        continue;
      }
    }
  }
}

void free_string(String *s) { free(s->buff); }

String read_till_space(String input, unsigned int offset) {
  String s = new_string();
  unsigned int curr_index = offset;
  while (input.buff[curr_index] != ' ') {
    if (input.length < curr_index) {
      break;
    }
    string_append(&s, input.buff[curr_index]);
    curr_index += 1;
  }
  return s;
}
BoardInput parse_input(String input) {
  BoardInput board_input;
  String row = read_till_space(input, 0);
  String col = read_till_space(input, row.length + 1);
  String f = read_till_space(input, col.length + row.length + 2);

  board_input.col = atoi(col.buff);
  board_input.row = atoi(row.buff);
  board_input.flag = strcmp(f.buff, "f");

  return board_input;
}
