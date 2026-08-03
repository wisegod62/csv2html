CC = gcc
CFLAGS = -Wall -Wextra -std=c17
TARGET = csv2html

all: main.c tokenizer.c
	$(CC) $(CFLAGS) main.c tokenizer.c -o $(TARGET)

clean:
	rm -f $(TARGET)

