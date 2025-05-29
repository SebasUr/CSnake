#include "score_board.h"
#include <stdlib.h>

// Creates and initializes a score_board structure with an ncurses window
score_board_t *score_board_create(int width, int y, int x) {
    score_board_t *score_board = malloc(sizeof(score_board_t));
    if (score_board == NULL) {
        return NULL; // Returns NULL if memory allocation fails
    }
    score_board->score_win = newwin(1, width, y, x); // Creates a window with height 1
    return score_board;
}

// Initializes the content of the score_board with a label and an initial value
void score_board_initialize(score_board_t *score_board, int initial_score) {
    score_board_clear(score_board); // Clears the window before displaying text
    mvwprintw(score_board->score_win, 0, 0, "Score:"); // Prints "Score:" at the beginning
    score_board_update(score_board, initial_score); // Displays the initial value
    score_board_refresh(score_board); // Refreshes to apply changes
}

// Updates the score value at the right corner of the window
void score_board_update(score_board_t *score_board, int score) {
    int height __attribute__((unused)), width;
    getmaxyx(score_board->score_win, height, width); // Gets window dimensions
    mvwprintw(score_board->score_win, 0, width - 11, "%11d", score); // Prints the score right-aligned
}

// Clears the content of the score_board window
void score_board_clear(score_board_t *score_board) {
    wclear(score_board->score_win);
}

// Refreshes the window to reflect changes on the screen
void score_board_refresh(score_board_t *score_board) {
    wrefresh(score_board->score_win);
}

// Frees resources associated with the score_board
void score_board_destroy(score_board_t *score_board) {
    if (score_board != NULL) {
        if (score_board->score_win != NULL) {
            delwin(score_board->score_win); // Deletes the ncurses window
        }
        free(score_board); // Frees the structure
    }
}
