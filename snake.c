#include "snake.h"
#include <stdlib.h>

void SnakePiece_init(SnakePiece* piece) {
    piece->x = 0;
    piece->y = 0;
    piece->icon = '#';
}

void SnakePiece_init_with_params(SnakePiece* piece, int y, int x) {
    piece->x = x;
    piece->y = y;
    piece->icon = '#';
}

void Snake_init(Snake* snake) {
    snake->pieces = NULL;
    snake->length = 0;
    snake->capacity = 0;
    snake->cur_direction = down;
}

void Snake_addPiece(Snake* snake, SnakePiece piece) {
    if (snake->length >= snake->capacity) {
        int new_capacity = snake->capacity == 0 ? 4 : snake->capacity * 2;
        SnakePiece* new_pieces = realloc(snake->pieces, new_capacity * sizeof(SnakePiece));
        if (!new_pieces) return;
        
        snake->pieces = new_pieces;
        snake->capacity = new_capacity;
    }

    for (int i = snake->length; i > 0; --i) {
        snake->pieces[i] = snake->pieces[i - 1];
    }

    snake->pieces[0] = piece;
    snake->length++;
}

void Snake_removePiece(Snake* snake) {
    if (snake->length > 0) {
        snake->length--;
    }
}

SnakePiece Snake_tail(Snake* snake) {
    if (snake->length == 0) {
        SnakePiece empty;
        SnakePiece_init(&empty);
        return empty;
    }
    return snake->pieces[snake->length - 1];
}

SnakePiece Snake_head(const Snake* snake) {
    if (snake->length == 0) {
        SnakePiece empty;
        SnakePiece_init(&empty);
        return empty;
    }
    return snake->pieces[0];
}

SnakePiece Snake_nextHead(const Snake* snake) {
    SnakePiece head = Snake_head(snake);  // Ahora compatible
    SnakePiece next_head = head;
    
    switch (snake->cur_direction) {
        case down:  next_head.y++; break;
        case up:    next_head.y--; break;
        case left:  next_head.x--; break;
        case right: next_head.x++; break;
    }
    
    return next_head;
}