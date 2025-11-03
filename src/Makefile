# Makefile for client1

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Target executable
TARGET = client1

# Source files
SRCS = client1.c client_utils.c

# Default rule
all: $(TARGET)

# How to build client1
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up generated files
clean:
	rm -f $(TARGET)
