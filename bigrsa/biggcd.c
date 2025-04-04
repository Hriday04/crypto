#include <string.h>
#include "../4096_t/4096_t.h"

void biggcd(uint64_t *a, uint64_t *b, uint64_t *g, uint64_t *x, uint64_t *y) {
    uint64_t old_r[S], r[S];
    uint64_t old_s[S], s[S];
    uint64_t old_t[S], t[S];
    uint64_t q[S], temp[S], temp2[S], zero[S];
    size_t i;

    for (i = 0; i < S; i++) {
        zero[i] = 0;
    }

    memcpy(old_r, a, BYTES);
    memcpy(r, b, BYTES);
    memset(old_s, 0, BYTES); old_s[0] = 1;
    memset(s, 0, BYTES);
    memset(old_t, 0, BYTES);
    memset(t, 0, BYTES); t[0] = 1;

    while (memcmp(r, zero, BYTES) != 0) {
        bigquo(old_r, r, q);

        bigmul(q, r, temp);
        bigsub(old_r, temp, temp2);
        memcpy(old_r, r, BYTES);
        memcpy(r, temp2, BYTES);

        bigmul(q, s, temp);
        bigsub(old_s, temp, temp2);
        memcpy(old_s, s, BYTES);
        memcpy(s, temp2, BYTES);

        bigmul(q, t, temp);
        bigsub(old_t, temp, temp2);
        memcpy(old_t, t, BYTES);
        memcpy(t, temp2, BYTES);
    }

    memcpy(g, old_r, BYTES);
    memcpy(x, old_s, BYTES);
    memcpy(y, old_t, BYTES);
}
