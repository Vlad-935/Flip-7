# Compiler setup.
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Define targets.
TARGETS = flip7

# Manually define all targets.
build: $(TARGETS)

runic: runic.c
	$(CC) $(CFLAGS) *.c -o Flip7

# Clean the solution.
clean:
	rm -f $(TARGETS)
