#include "board.h"

void board_add_border(board_t *board) {
    box(board->win, 0, 0);
}

void board_clear(board_t *board) {
    wclear(board->win);
    board_add_border(board);
}

void board_refresh(board_t *board) {
    wrefresh(board->win);
}

void board_place_char(board_t *board, int x, int y, chtype ch) {
    mvwaddch(board->win, y, x, ch);
}

chtype board_get_chart_at(board_t *board, int x, int y) {
    return mvwinch(board->win, y, x);
}

chtype board_get_input(board_t *board) {
    return wgetch(board->win);
}

void board_get_empty_space(board_t *board, int *x, int *y) {
    while (mvwinch(board->win, *y, *x) != ' ') {
        *x = rand() % (board->cols);
        *y = rand() % (board->rows);
    }
}

board_t *board_initialize(int rows, int cols) {
    board_t *board = malloc(sizeof(board_t));
    if (board == NULL) {
        return NULL;
    }

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    board->startRow = (yMax / 2) - (rows/2);
    board->startCol = (xMax / 2) - (cols/2);
    board->win = newwin(rows, cols, board->startRow, board->startCol);
    wtimeout(board->win, 500);

    board->cols = cols;
    board->rows = rows;
    board_clear(board);
    board_refresh(board);
    keypad(board->win, TRUE);
    return board;
}

void board_add(board_t *board, SnakePiece piece) {
    board_place_char(board, piece.x, piece.y, piece.icon);
}