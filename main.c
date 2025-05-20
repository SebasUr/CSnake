#include "snake_game.h"

#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5

int main() {
    initscr();
    refresh();

    noecho();

    snake_game_t *game = snake_game_initialize(BOARD_ROWS, BOARD_COLS);
    if (game == NULL) {
        endwin();
        return 1; 
    }

    // Main game loop
    while (!game->game_over) {
        snake_game_process_input(game);
        snake_game_update_state(game);
        snake_game_redraw(game);
    }

    snake_game_destroy(game);

    getch();
    endwin();

    return 0;
}