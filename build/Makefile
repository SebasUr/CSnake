CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I../include
LDFLAGS = -lncurses

SRC_DIR = ../src
OBJ_DIR = .
INCLUDE_DIR = ../include

SRCS = $(SRC_DIR)/main.c \
	   $(SRC_DIR)/board.c \
	   $(SRC_DIR)/snake.c \
	   $(SRC_DIR)/snake_game.c \
	   $(SRC_DIR)/score_board.c \
	   $(SRC_DIR)/menu.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = ../main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean