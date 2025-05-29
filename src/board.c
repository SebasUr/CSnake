#include "board.h"

void board_add_border(board_t *board) {
    box(board->win, 0, 0);  // Draws a border around the window
}

void board_clear(board_t *board) {
    wclear(board->win);          // Clears all content from the window
    board_add_border(board);     // Redraws the border after clearing
}

void board_refresh(board_t *board) {
    wrefresh(board->win);  // Updates the screen with changes made to the window
}

void board_place_char(board_t *board, int x, int y, chtype ch) {
    mvwaddch(board->win, y, x, ch);  // Places a character at a specific position
}

chtype board_get_chart_at(board_t *board, int x, int y) {
    return mvwinch(board->win, y, x);  // Returns the character at a specific board position
}

chtype board_get_input(board_t *board) {
    return wgetch(board->win);  // Waits for user input inside the board window
}

void board_get_empty_space(board_t *board, int *x, int *y) {
    // Finds a random position that is empty (' ')
    while (mvwinch(board->win, *y, *x) != ' ') {
        *x = rand() % (board->cols);
        *y = rand() % (board->rows);
    }
}

board_t *board_initialize(int rows, int cols) {
    board_t *board = malloc(sizeof(board_t));
    if (board == NULL) {
        return NULL;  // Memory allocation failed
    }

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);  // Gets terminal dimensions

    // Calculates the starting position to center the board on screen
    board->startRow = (yMax / 2) - (rows/2);
    board->startCol = (xMax / 2) - (cols/2);

    board->win = newwin(rows, cols, board->startRow, board->startCol);  // Creates the board window
    wtimeout(board->win, 500);  // Sets timeout for user input (ms)

    board->cols = cols;
    board->rows = rows;

    board_clear(board);     // Clears and draws the border
    board_refresh(board);   // Displays the initial state

    keypad(board->win, TRUE);  // Enables use of special keys (like arrows)
    return board;
}

void board_add(board_t *board, SnakePiece piece) {
    board_place_char(board, piece.x, piece.y, piece.icon);  // Draws a snake piece or food
}
