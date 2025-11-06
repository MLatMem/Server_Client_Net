# Makefile for client1 and client2

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Default rule
all: client1 client2

# Build client1
client1: client1.c client_utils.c
	$(CC) $(CFLAGS) -o client1 client1.c client_utils.c

# Build client2
client2: client2.c client_utils.c
	$(CC) $(CFLAGS) -o client2 client2.c client_utils.c

# Clean up
clean:
	rm -f client1 client2 *.o