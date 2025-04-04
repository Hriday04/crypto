#include <gmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define S 64
#define BYTES (S * sizeof(uint64_t))

void prigmp(uint64_t *big, uint8_t words) {
    mpz_t m;
    FILE *fp;
    size_t read;

    fp = fopen("/dev/random", "r");
    if (!fp) {
        perror("fopen");
        return;
    }

    memset(big, 0, BYTES);
    read = fread(big, sizeof(uint64_t), words, fp);
    if (read != words) {
        fprintf(stderr, "Error: could not read enough random data.\n");
        fclose(fp);
        return;
    }
    fclose(fp);

    mpz_init(m);
    mpz_import(m, words, -1, sizeof(uint64_t), 0, 0, big);
    mpz_nextprime(m, m);
    mpz_export(big, NULL, -1, sizeof(uint64_t), 0, 0, m);
    mpz_clear(m);
}
