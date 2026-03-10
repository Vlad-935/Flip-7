CC = gcc
CFLAGS = -I./include -Wall

# Listăm toate fișierele sursă
SRCS = flip7.c source/cards.c

# Generăm numele executabilului
TARGET = flip7

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)