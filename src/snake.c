#include "snake.h"
#include <stdlib.h>

// Initializes a snake piece at (0,0) with the default icon 'O'
void SnakePiece_init(SnakePiece* piece) {
    piece->x = 0;
    piece->y = 0;
    piece->icon = 'O';
}

// Initializes a snake piece with specific coordinates
void SnakePiece_init_with_params(SnakePiece* piece, int y, int x) {
    piece->x = x;
    piece->y = y;
    piece->icon = 'O';
}

// Initializes the Snake structure with default values
void Snake_init(Snake* snake) {
    snake->pieces = NULL;
    snake->length = 0;
    snake->capacity = 0;
    snake->cur_direction = down;
}

// Adds a new piece at the start of the snake (head)
// Reallocates memory if current capacity is exceeded
void Snake_addPiece(Snake* snake, SnakePiece piece) {
    if (snake->length >= snake->capacity) {
        int new_capacity = snake->capacity == 0 ? 4 : snake->capacity * 2;
        SnakePiece* new_pieces = realloc(snake->pieces, new_capacity * sizeof(SnakePiece));
        if (!new_pieces) return;
        
        snake->pieces = new_pieces;
        snake->capacity = new_capacity;
    }

    // Shifts all pieces to the right to insert the new head
    for (int i = snake->length; i > 0; --i) {
        snake->pieces[i] = snake->pieces[i - 1];
    }

    snake->pieces[0] = piece;
    snake->length++;
}

// Removes the last piece of the snake (tail)
void Snake_removePiece(Snake* snake) {
    if (snake->length > 0) {
        snake->length--;
    }
}

// Returns the piece representing the tail of the snake
SnakePiece Snake_tail(Snake* snake) {
    if (snake->length == 0) {
        SnakePiece empty;
        SnakePiece_init(&empty);
        return empty;
    }
    return snake->pieces[snake->length - 1];
}

// Returns the piece representing the head of the snake
SnakePiece Snake_head(const Snake* snake) {
    if (snake->length == 0) {
        SnakePiece empty;
        SnakePiece_init(&empty);
        return empty;
    }
    return snake->pieces[0];
}

// Calculates and returns the next position of the head based on the current direction
SnakePiece Snake_nextHead(const Snake* snake) {
    SnakePiece head = Snake_head(snake);  // Copy the current head
    SnakePiece next_head = head;
    
    switch (snake->cur_direction) {
        case down:  next_head.y++; break;
        case up:    next_head.y--; break;
        case left:  next_head.x--; break;
        case right: next_head.x++; break;
    }
    
    return next_head;
}
