#include "snake_game.h"
#include <stdlib.h>
#include <time.h>
#include "menu.h"

#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS (int)(BOARD_DIM * 2.5)  // 2.5 is used to give more width to the board

void show_start_menu();

int main() {
    initscr();  // Initializes ncurses

    if (has_colors()) {
        start_color();  // Enables colors if available
    }

    keypad(stdscr, TRUE);  // Allows capturing arrow keys and special keys
    noecho();              // Do not display user input
    curs_set(0);           // Hides the cursor
    srand(time(NULL));     // Initializes the seed for random numbers

    while (1) {
        show_start_menu();  // Start menu (likely waits for a key)

        // Creates a new game instance
        snake_game_t *game = snake_game_initialize(BOARD_ROWS, BOARD_COLS);

        while (!game->game_over) {
            snake_game_process_input(game);  // Reads keys and updates direction
            snake_game_update_state(game);   // Game logic (collisions, movement)
            snake_game_redraw(game);         // Redraws the screen
        }

        snake_game_destroy(game);  // Frees game memory and resources
    }

    endwin();  // Ends ncurses and cleans the terminal
    return 0;
}
