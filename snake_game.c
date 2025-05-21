#include "snake_game.h"

snake_game_t *snake_game_initialize(int rows, int cols) {
    snake_game_t *game = malloc(sizeof(snake_game_t));
    if (game == NULL) {
        return NULL;
    }

    game->board = board_initialize(rows, cols);
    if (game->board == NULL) {
        free(game);
        return NULL;
    }

    game->game_over = false;
    game->apple_x = -1;
    game->apple_y = -1;
    srand(time(NULL));
    game->snake.cur_direction = down;
    SnakePiece next;
    SnakePiece_init_with_params(&next, 1, 1);

    board_add(game->board, next);
    Snake_addPiece(&game->snake, next);

    next = Snake_nextHead(&game->snake);
    board_add(game->board, next);
    Snake_addPiece(&game->snake, next);

    next = Snake_nextHead(&game->snake);
    board_add(game->board, next);
    Snake_addPiece(&game->snake, next);

    game->snake.cur_direction = right;

    next = Snake_nextHead(&game->snake);
    board_add(game->board, next);
    Snake_addPiece(&game->snake, next);

    return game;
}

void snake_game_process_input(snake_game_t *game) {
    chtype input = board_get_input(game->board);
    switch (input) {
        case 'q':
            game->game_over = true;
            break;
        default:
            break;
    }
}

void snake_game_update_state(snake_game_t *game) {
    if (game->apple_x == -1 && game->apple_y == -1) {
        int x, y;
        board_get_empty_space(game->board, &x, &y);
        game->apple_x = x;
        game->apple_y = y;
        board_place_char(game->board, x, y, 'A');
    }
    SnakePiece next = Snake_nextHead(&game->snake);;
    if(next.x != game->apple_x && next.y != game->apple_y){
        int emptyRow = Snake_tail(&game->snake).y;
        int emptyCol = Snake_tail(&game->snake).x;
        board_place_char(game->board, emptyCol, emptyRow, ' ');
        Snake_removePiece(&game->snake);
    }
    board_add(game->board, next);
    Snake_addPiece(&game->snake, next);
}

void snake_game_redraw(snake_game_t *game) {
    board_refresh(game->board);
}

void snake_game_destroy(snake_game_t *game) {
    if (game != NULL) {
        if (game->board != NULL) {
            delwin(game->board->win);
            free(game->board);
        }
        free(game);
    }
}