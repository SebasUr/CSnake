#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include <string.h>
#include <stdbool.h>

#define MAX_DEMO_SNAKES 5
#define MAX_LENGTH 10

typedef struct {
    int y, x;
    int dx;
    int length;
    char body[MAX_LENGTH][2];
} demo_snake_t;

void show_start_menu() {
    clear();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    // Inicializar colores
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Solo para la palabra "Snake"

    demo_snake_t snakes[MAX_DEMO_SNAKES];

    int text_y = rows / 2 - 1;
    int text_x_start = (cols - 22) / 2;
    int text_x_end = text_x_start + 21;

    const char* title[] = {
        "  _____             _        ",
        " / ____|           | |       ",
        "| (___   __    __ _| | _____ ",
        " \\___ \\ / _ \\ / _` | |/ / _ \\",
        " ____) | | | | (_| |   <  __/",
        "|_____/|_| |_|\\__,_|_|\\_\\___|"
    };
    int title_lines = sizeof(title) / sizeof(title[0]);
    int title_y = 3;
    int title_x = (cols - strlen(title[0])) / 2;

    srand(time(NULL));
    for (int i = 0; i < MAX_DEMO_SNAKES; i++) {
        snakes[i].length = 3 + rand() % (MAX_LENGTH - 3);  // Longitudes entre 3 y 10
        snakes[i].y = rand() % rows;
        snakes[i].x = rand() % cols;
        snakes[i].dx = (rand() % 2 == 0) ? 1 : -1;
        for (int j = 0; j < snakes[i].length; j++) {
            snakes[i].body[j][0] = snakes[i].y;
            snakes[i].body[j][1] = snakes[i].x - j * snakes[i].dx;
        }
    }

    timeout(100);
    int ch;
    while ((ch = getch()) != '\n') {
        if (ch == 'q' || ch == 'Q') {
            endwin();
            exit(0);
        }

        clear();

        // Mostrar título completo en color verde
        attron(COLOR_PAIR(1));
        for (int i = 0; i < title_lines; i++) {
            mvprintw(title_y + i, title_x, "%s", title[i]);
        }
        attroff(COLOR_PAIR(1));

        // Mostrar instrucciones
        mvprintw(text_y, text_x_start, "Press ENTER to Start");
        mvprintw(rows - 1, 2, "Press 'q' to quit");

        // Dibujar serpientes demo
        for (int i = 0; i < MAX_DEMO_SNAKES; i++) {
            mvaddch(snakes[i].body[snakes[i].length - 1][0],
                    snakes[i].body[snakes[i].length - 1][1], ' ');

            for (int j = snakes[i].length - 1; j > 0; j--) {
                snakes[i].body[j][0] = snakes[i].body[j - 1][0];
                snakes[i].body[j][1] = snakes[i].body[j - 1][1];
            }

            snakes[i].x += snakes[i].dx;
            if (snakes[i].x < 0 || snakes[i].x >= cols) {
                snakes[i].x = (snakes[i].dx == 1) ? 0 : cols - 1;
                snakes[i].y = rand() % rows;
            }

            snakes[i].body[0][0] = snakes[i].y;
            snakes[i].body[0][1] = snakes[i].x;

            for (int j = 0; j < snakes[i].length; j++) {
                int y = snakes[i].body[j][0];
                int x = snakes[i].body[j][1];

                bool overlaps_text = (y == text_y && x >= text_x_start && x <= text_x_end);
                bool overlaps_title = (y >= title_y && y < title_y + title_lines &&
                                       x >= title_x && x < title_x + (int)strlen(title[0]));

                if (overlaps_text || overlaps_title) {
                    mvaddch(y, x, ' ');
                    continue;
                }

                mvaddch(y, x, j == 0 ? (snakes[i].dx == 1 ? '>' : '<') : 'O');
            }
        }

        refresh();
    }

    // Limpiar pantalla al salir
    clear();
    refresh();
    timeout(-1);
}
