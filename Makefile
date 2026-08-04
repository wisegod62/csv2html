# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c17

# Name of your final executable program
TARGET = csv2html

# Default target: builds the executable
all: main.c tokenizer.c
	$(CC) $(CFLAGS) main.c tokenizer.c -o $(TARGET)

# Automated test target: builds the program and executes the bash script
test: all
	@echo "🧪 Executing automated testing suite..."
	./tests/run_tests.sh

# Clean target: wipes compiled binaries out of your workspace
clean:
	rm -f $(TARGET)

# Declares targets that aren't physical files to prevent conflicts
.PHONY: all test clean

