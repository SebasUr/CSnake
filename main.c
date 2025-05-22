#include "snake_game.h"

#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5

int main() {
    initscr();

    // Verificación de colores en la terminal.
    if (has_colors()) {
        start_color();
    }
    keypad(stdscr, TRUE);
    refresh();

    noecho();
    curs_set(0);

    snake_game_t *game = snake_game_initialize(BOARD_ROWS, BOARD_COLS);

    // Main game loop
    while (!game->game_over) {
        snake_game_process_input(game);
        snake_game_update_state(game);
        snake_game_redraw(game);
    }
    

    snake_game_destroy(game);

    getch();
    endwin();
    printf("Game Over!\n");
    return 0;
}