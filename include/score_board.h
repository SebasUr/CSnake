#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H

#include <ncurses.h>

typedef struct {
    WINDOW *score_win;
} score_board_t;

score_board_t *score_board_create(int width, int y, int x);
void score_board_initialize(score_board_t *score_board, int initial_score);
void score_board_update(score_board_t *score_board, int score);
void score_board_clear(score_board_t *score_board);
void score_board_refresh(score_board_t *score_board);
void score_board_destroy(score_board_t *score_board);

#endif
