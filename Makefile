# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Target executable name
TARGET = main

# Build rule
all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Clean rule to remove compiled files
clean:
	rm -f $(TARGET) *.o
