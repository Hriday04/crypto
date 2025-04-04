/* bigkey.c - 4096-bit RSA Key Generation (C89 compliant) */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../4096_t/4096_t.h"

void prigmp(uint64_t *big, uint8_t words);
void biggcd(uint64_t *a, uint64_t *b, uint64_t *g, uint64_t *x, uint64_t *y);

void fprinthex(FILE *fp, uint64_t *a) {
    int i;
    for (i = S - 1; i >= 0; i--) {
        fprintf(fp, "%016lx", a[i]);
    }
    fprintf(fp, "\n");
}

int main() {
    uint64_t p[S], q[S], n[S], phi[S], one[S];
    uint64_t e[S], d[S], g[S], y[S];
    uint64_t p1[S], q1[S];
    FILE *bad, *pub;

    /* Generate random primes p and q */
    prigmp(p, S);
    prigmp(q, S);

    /* Compute n = p * q */
    bigmul(p, q, n);

    /* Compute phi = (p - 1)(q - 1) */
    memset(one, 0, BYTES);
    one[0] = 1;
    bigsub(p, one, p1);
    bigsub(q, one, q1);
    bigmul(p1, q1, phi);

    /* Set e = 65537 */
    memset(e, 0, BYTES);
    e[0] = 65537;

    /* Compute d = e^-1 mod phi using biggcd */
    biggcd(e, phi, g, d, y);
    if (memcmp(g, one, BYTES) != 0) {
        fprintf(stderr, "Error: gcd(e, phi) != 1\n");
        return 1;
    }

    /* Write to unsafe.bad */
    bad = fopen("unsafe.bad", "w");
    if (!bad) {
        perror("fopen (bad)");
        return 1;
    }
    fprintf(bad, "-----BEGIN UNSAFE PRIVATE KEY-----\n");
    fprinthex(bad, n);
    fprinthex(bad, e);
    fprinthex(bad, d);
    fprintf(bad, "-----END UNSAFE PRIVATE KEY-----\n");
    fclose(bad);

    /* Write to unsafe.pub */
    pub = fopen("unsafe.pub", "w");
    if (!pub) {
        perror("fopen (pub)");
        return 1;
    }
    fprintf(pub, "-----BEGIN UNSAFE PUBLIC KEY-----\n");
    fprinthex(pub, n);
    fprinthex(pub, e);
    fprintf(pub, "-----END UNSAFE PUBLIC KEY-----\n");
    fclose(pub);

    return 0;
}
