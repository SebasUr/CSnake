#pragma once
#include <ncurses.h>

typedef enum {
    up,
    down,
    left,
    right
} Directions;

typedef struct {
    int x;
    int y;
    char icon;
} SnakePiece;

typedef struct {
    SnakePiece* pieces; 
    int length;         
    int capacity;
    Directions cur_direction;
} Snake;

// Funciones de SnakePiece
void SnakePiece_init(SnakePiece* piece);
void SnakePiece_init_with_params(SnakePiece* piece, int y, int x);

// Funciones de Snake (equivalentes a los métodos de la clase)
void Snake_init(Snake* snake);
void Snake_addPiece(Snake* snake, SnakePiece piece);
void Snake_removePiece(Snake* snake);
SnakePiece Snake_tail(Snake* snake);
SnakePiece Snake_head(const Snake* snake);
Directions Snake_getDirection(const Snake* snake);
void Snake_setDirection(Snake* snake, Directions new_direction);
SnakePiece Snake_nextHead(const Snake* snake);