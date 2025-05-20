#pragma once

#include <ncurses.h>
#include <stdlib.h>

typedef struct {
    WINDOW *win;
    int rows;
    int cols;
} board_t;

void board_add_border(board_t *board);
void board_clear(board_t *board);
void board_refresh(board_t *board);
void board_place_char(board_t *board, int x, int y, chtype ch);
void board_get_empty_space(board_t *board, int *x, int *y);
chtype board_get_input(board_t *board);
board_t *board_initialize(int rows, int cols);