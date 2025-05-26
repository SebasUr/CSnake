#pragma once

#include <time.h>
#include "board.h"
#include "score_board.h"
#include "snake.h"

typedef struct {
    board_t *board;
    score_board_t *score_board;
    int score;
    bool game_over;
    int apple_x;
    int apple_y;
    Snake snake;
} snake_game_t;

snake_game_t *snake_game_initialize(int rows, int cols);
void snake_game_update_state(snake_game_t *game);
void snake_game_process_input(snake_game_t *game);
void snake_game_redraw(snake_game_t *game);
void snake_game_destroy(snake_game_t *game);
void Snake_reset(Snake *snake);
int get_score();