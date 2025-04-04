CC = gcc
CFLAGS = -std=c89 -Wall -Wextra -Werror -Wpedantic -O2
CLIBS = -lgmp
BIGNUM = ../4096_t/4096_t.c

all: bigkey bigrsa

bigkey: bigkey.c BigRNG.c biggcd.c $(BIGNUM)
	$(CC) bigkey.c BigRNG.c biggcd.c $(BIGNUM) $(CFLAGS) -o bigkey $(CLIBS)

clean:
	rm -f bigkey unsafe.* *.txt

bigrsa: bigrsa.c BigRNG.c biggcd.c $(BIGNUM)
	$(CC) bigrsa.c BigRNG.c biggcd.c $(BIGNUM) $(CFLAGS) -o bigrsa $(CLIBS)
