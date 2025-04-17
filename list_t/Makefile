CC = gcc
CFLAGS = -std=c89 -Wall -Wextra -pedantic

all: tester

tester: tester.c list_t.c
	$(CC) $(CFLAGS) -o tester tester.c list_t.c

clean:
	rm -f tester
