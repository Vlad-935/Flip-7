# Compiler setup.
CC = gcc
CFLAGS = -I./include -Wall -Wextra -std=c99

# Define targets.
TARGETS = Flip7

# Manually define all targets.
build: $(TARGETS)

Flip7: flip7.c
	$(CC) $(CFLAGS) *.c -o Flip7

# Clean the solution.
clean:
	rm -f $(TARGETS)
