CC = gcc
CFLAGS = -std=c89 -Wall -Wextra -pedantic

all: tester

tester: tester.c heap_t.c
	$(CC) $(CFLAGS) -o tester tester.c heap_t.c

clean:
	rm -f tester
