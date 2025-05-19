CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -lncurses

SRCS = main.c

OBJS = $(SRCS:.c=.o)

# Ejecutable
TARGET = main

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Regla para compilar archivos .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpieza
clean:
	rm -f $(OBJS) $(TARGET)