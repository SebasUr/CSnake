#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include "snake.h"

typedef struct {
    WINDOW *win;
    int rows;
    int cols;
    int startRow;
    int startCol;
} board_t;

void board_add_border(board_t *board);
void board_clear(board_t *board);
void board_refresh(board_t *board);
void board_place_char(board_t *board, int x, int y, chtype ch);
chtype board_get_chart_at(board_t *board, int x, int y);
void board_get_empty_space(board_t *board, int *x, int *y);
chtype board_get_input(board_t *board);
board_t *board_initialize(int rows, int cols);
void board_add(board_t *board, SnakePiece piece);