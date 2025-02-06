#define S (sizeof(unsigned) << 3)

char *u2b(unsigned u, char *b) {
    unsigned i = 0;
    for (; i < S; i++) { b[i] = (u >> i) & 1; }
    return b;
}

unsigned b2u(char *b) {
    unsigned u = 0, i = 0;
    for (; i < S; i++) { u += b[i] << i; }
    return u;
}

unsigned choice(unsigned a, unsigned b, unsigned c) {
    unsigned vals[4] = {a, b, c}, i = 0;
    char buf[3][S];
    for (i = 0; i < 3; i++) { u2b(vals[i], buf[i]); }
    for (i = 0; i < S; i++) { buf[0][i] = buf[0][i] ? buf[1][i] : buf[2][i]; }
    return b2u(buf[0]);
}

unsigned median(unsigned a, unsigned b, unsigned c)  {
    unsigned vals[4] = {a, b, c}, i = 0;
    char buf[3][S];
    for (i = 0; i < 3; i++) { u2b(vals[i], buf[i]); }
    for (i = 0; i < S; i++) { buf[0][i] = (buf[0][i] + buf[1][i] + buf[2][i]) >> 1; }
    return b2u(buf[0]);
}

unsigned rotate(unsigned a, unsigned b) {
    char buf[2][S];
    unsigned i;
    u2b(a, buf[0]);
    for (i = 0; i < S; i++) { buf[1][i] = buf[0][(i + b) % S]; }
    return b2u(buf[1]);
}

int main() {
    /* Various Variables*/
    unsigned a[3], i, buf[8] = 
    {0, 1, 2, 4, 8, 16, 24, 32};

    /* Random values from memory address... */
    /* use "-Wno-pointer-to-int-cast" */
    a[0] = (unsigned)(&a) | ((long)(&a) >> 32) * (unsigned)(&a) + 1;
    a[1] = (unsigned)(&a) ^ ((long)(&a) >> 32) * (unsigned)(&a) + 2;
    a[2] = (unsigned)(&a) & ((long)(&a) >> 32) * (unsigned)(&a) + 3;

    /* CHOICE */
    for (i = 0; i < 3; i++) {
        if (CHOICE(a[(i+0)%3],a[(i+1)%3],a[(i+2)%3]) !=
            choice(a[(i+0)%3],a[(i+1)%3],a[(i+2)%3])) {
            return 1;
        }
    }

    /* MEDIAN */
    for (i = 0; i < 3; i++) {
        if (MEDIAN(a[(i+0)%3],a[(i+1)%3],a[(i+2)%3]) !=
            median(a[(i+0)%3],a[(i+1)%3],a[(i+2)%3])) {
            return 2;
        }
        a[i] = ~a[i];
    }

    /* ROTATE */
    for (i = 0; i < 8; i++) {
        if (ROTATE(a[0], buf[i]) != rotate(a[0], buf[i]) &&
            ROTATE(a[1], buf[i]) != rotate(a[1], buf[i]) &&
            ROTATE(a[2], buf[i]) != rotate(a[2], buf[i])) {
            return 3;
        }
    }
    return 0;
}
