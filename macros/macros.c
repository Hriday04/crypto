#ifndef MACROS_H
#define MACROS_H

/* Bitwise Choice Macro */
#define CHOICE(e, f, g) ((e & f) ^ (~e & g))

/* Bitwise Median Macro */
#define MEDIAN(e, f, g) ((e & f) | (f & g) | (g & e))

/* Right Rotate Macro */
#define ROTATE(a, b) ((a >> b) | (a << (32 - b)))

#endif /* MACROS_H */
