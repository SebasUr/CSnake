CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lncurses

SRCS = main.c \
       board.c \
       snake.c \
       snake_game.c

OBJS = $(SRCS:.c=.o)

TARGET = snake_game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean