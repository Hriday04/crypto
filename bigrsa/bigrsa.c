#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../4096_t/4096_t.h"

void hex_to_big(uint64_t *out, const char *hex) {
    size_t len = strlen(hex);
    size_t i, j = 0;
    memset(out, 0, BYTES);

    for (i = len; i > 0; i -= 16) {
        char chunk[17];
        size_t start = (i >= 16) ? i - 16 : 0;
        size_t clen = i - start;
        memset(chunk, 0, 17);
        strncpy(chunk, hex + start, clen);
        sscanf(chunk, "%16lx", &out[j]);
        j++;
    }
}

void bigpowmod(uint64_t *base, uint64_t *exp, uint64_t *mod, uint64_t *result) {
    uint64_t res[S], tmp[S], two[S];
    size_t i, j;

    memset(res, 0, BYTES);
    res[0] = 1;
    memcpy(tmp, base, BYTES);

    memset(two, 0, BYTES);
    two[0] = 2;

    for (i = 0; i < S; i++) {
        for (j = 0; j < 64; j++) {
            if ((exp[i] >> j) & 1) {
                bigmul(res, tmp, res);
                bigrem(res, mod, res);
            }
            bigmul(tmp, tmp, tmp);
            bigrem(tmp, mod, tmp);
        }
    }
    memcpy(result, res, BYTES);
}

void load_key(const char *filename, uint64_t *n, uint64_t *e_or_d, int is_private) {
    FILE *fp = fopen(filename, "r");
    char line[8192];

    if (!fp) {
        perror("fopen");
        exit(1);
    }

    fgets(line, sizeof(line), fp); // header
    fgets(line, sizeof(line), fp); hex_to_big(n, line);     // n
    fgets(line, sizeof(line), fp); hex_to_big(e_or_d, line); // e or d

    if (is_private) {
        fgets(line, sizeof(line), fp); // skip d line (already read)
        fgets(line, sizeof(line), fp); // footer
    } else {
        fgets(line, sizeof(line), fp); // footer
    }

    fclose(fp);
}

void read_bytes(const char *filename, uint64_t *out) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("read file");
        exit(1);
    }
    memset(out, 0, BYTES);
    fread(out, 1, BYTES, fp);
    fclose(fp);
}

void write_bytes(const char *filename, uint64_t *in) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("write file");
        exit(1);
    }
    fwrite(in, 1, BYTES, fp);
    fclose(fp);
}

int main(int argc, char **argv) {
    uint64_t n[S], exp[S], input[S], output[S];
    int is_decrypt;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s -e|-d input.txt output.txt\n", argv[0]);
        return 1;
    }

    is_decrypt = (strcmp(argv[1], "-d") == 0);

    if (is_decrypt) {
        load_key("unsafe.bad", n, exp, 1);
    } else {
        load_key("unsafe.pub", n, exp, 0);
    }

    read_bytes(argv[2], input);
    bigpowmod(input, exp, n, output);
    write_bytes(argv[3], output);

    return 0;
}
