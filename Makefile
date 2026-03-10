CC = gcc
CFLAGS = -I./cards -Wall

# Listăm toate fișierele sursă
SRCS = flip7.c cards/cards.c

# Generăm numele executabilului
TARGET = flip7

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)