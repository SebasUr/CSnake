#include "snake_game.h"

snake_game_t *snake_game_initialize(int rows, int cols) {
    snake_game_t *game = malloc(sizeof(snake_game_t));
    Snake_reset(&game->snake);
    if (game == NULL) {
        return NULL;
    }

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Cabeza
        init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Cuerpo
        init_pair(3, COLOR_RED, COLOR_BLACK);    // Manzana
    }

    game->board = board_initialize(rows, cols);
    if (game->board == NULL) {
        free(game);
        return NULL;
    }

    int sb_row = game->board->startRow + rows;
    int sb_col = game->board->startCol;
    
    game->score_board = score_board_create(cols, sb_row, sb_col);
    if (game->score_board == NULL) {
        free(game);
        return NULL;
    }

    score_board_initialize(game->score_board, 0);
    game->score = 0;

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
        case KEY_UP:
            if (game->snake.cur_direction != down) {
                game->snake.cur_direction = up;
            }
            break;
        case KEY_DOWN:
            if (game->snake.cur_direction != up) {
                game->snake.cur_direction = down;
            }
            break;
        case KEY_LEFT:
            if (game->snake.cur_direction != right) {
                game->snake.cur_direction = left;
            }
            break;
        case KEY_RIGHT:
            if (game->snake.cur_direction != left) {
                game->snake.cur_direction = right;
            }
            break;
        case 'p':
            while (true) {
                chtype pause_input = board_get_input(game->board);
                if (pause_input == 'p') {
                    break; 
                }
            }
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
        // Manzana en rojo
        board_place_char(game->board, x, y, 'X' | COLOR_PAIR(3));
    }
    SnakePiece next = Snake_nextHead(&game->snake);
    
    switch (game->snake.cur_direction) {
        case up:
            next.icon = '^';
            break;
        case down:
            next.icon = 'v';
            break;
        case left:
            next.icon = '<';
            break;
        case right:
            next.icon = '>';
            break;
    }
    
    if(next.x == game->apple_x && next.y == game->apple_y) {
        // Reset para generar nueva manzana
        game->apple_x = -1; 
        game->apple_y = -1;
        game->score += 100;
        score_board_update(game->score_board, game->score);
    } else if(board_get_chart_at(game->board, next.x, next.y) != ' ') {
        game->game_over = true;
        return;
    } else {
        int emptyRow = Snake_tail(&game->snake).y;
        int emptyCol = Snake_tail(&game->snake).x;
        board_place_char(game->board, emptyCol, emptyRow, ' ');
        Snake_removePiece(&game->snake);
    }
    
    Snake_addPiece(&game->snake, next);
    
    for (int i = 0; i < game->snake.length; i++) {
        char icon = (i == 0) ? game->snake.pieces[i].icon : 'O';
        // Cabeza en amarillo, cuerpo en verde
        int color_pair = (i == 0) ? COLOR_PAIR(1) : COLOR_PAIR(2);
        board_place_char(game->board, game->snake.pieces[i].x, game->snake.pieces[i].y, icon | color_pair);
    }
}

void snake_game_redraw(snake_game_t *game) {
    board_refresh(game->board);
    score_board_refresh(game->score_board);
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

void Snake_reset(Snake *snake) {
    snake->length = 0;
    snake->cur_direction = right;
}
