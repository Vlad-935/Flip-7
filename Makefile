# Compiler setup.
CC = gcc
CFLAGS = -I./include -Wall -Wextra

# Search for .c files
SRC_DIR = source

SRCS = flip7.c $(wildcard $(SRC_DIR)/*.c)
HDRS = $(wildcard include/*.h) 
OBJS = $(SRCS:.c=.o)

# Define targets.
TARGET = Flip7

# Manually define all targets.
build: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	rm -f $(OBJS)

# Searching for headers
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the solution.
clean:
	rm -f $(OBJS) $(TARGETS)

