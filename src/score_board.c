#include "score_board.h"
#include <stdlib.h>

score_board_t *score_board_create(int width, int y, int x) {
    score_board_t *score_board = malloc(sizeof(score_board_t));
    if (score_board == NULL) {
        return NULL;
    }
    score_board->score_win = newwin(1, width, y, x);
    return score_board;
}

void score_board_initialize(score_board_t *score_board, int initial_score) {
    score_board_clear(score_board);
    mvwprintw(score_board->score_win, 0, 0, "Score:");
    score_board_update(score_board, initial_score);
    score_board_refresh(score_board);
}

void score_board_update(score_board_t *score_board, int score) {
    int height __attribute__((unused)), width;
    getmaxyx(score_board->score_win, height, width);
    mvwprintw(score_board->score_win, 0, width - 11, "%11d", score);
}

void score_board_clear(score_board_t *score_board) {
    wclear(score_board->score_win);
}

void score_board_refresh(score_board_t *score_board) {
    wrefresh(score_board->score_win);
}

void score_board_destroy(score_board_t *score_board) {
    if (score_board != NULL) {
        if (score_board->score_win != NULL) {
            delwin(score_board->score_win);
        }
        free(score_board);
    }
}
