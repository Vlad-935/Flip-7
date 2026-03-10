# Compiler setup.
CC = gcc
CFLAGS = -I./include -Wall -Wextra

# Search for .c files
SRC_DIR = source

SRCS = $(wildcard $(SRC_DIR)/*.c)

# Define targets.
TARGET = Flip7

# Manually define all targets.
build: $(TARGET)

Flip7: flip7.c
	$(CC) $(CFLAGS) $(SRCS) -o Flip7

# Clean the solution.
clean:
	rm -f $(TARGETS)
