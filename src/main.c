#include "snake_game.h"
#include <stdlib.h>
#include <time.h>
#include "menu.h"

#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS (int)(BOARD_DIM * 2.5)

void show_start_menu();

int main() {
    initscr();
    if (has_colors()) {
        start_color();
    }
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    srand(time(NULL));

    while (1) {
        show_start_menu();

        snake_game_t *game = snake_game_initialize(BOARD_ROWS, BOARD_COLS);

        while (!game->game_over) {
            snake_game_process_input(game);
            snake_game_update_state(game);
            snake_game_redraw(game);
        }

        snake_game_destroy(game);
    }

    endwin();
    return 0;
}
